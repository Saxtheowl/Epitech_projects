#!/usr/bin/env python3
#
# EPITECH PROJECT, 2025
# Whanos_roro
# File description:
#   Generate basic K8s manifests from whanos.yml
#

import os
import re
import sys
from typing import Dict, List, Tuple


def parse_whanos_yml(path: str) -> Dict:
    """
    Minimal parser for a subset of YAML used by whanos.yml.
    Extracts: deployment.replicas (int), deployment.ports (list[int]).
    Unknown fields are ignored.
    """
    data = {"deployment": {}}
    dep = data["deployment"]
    in_dep = False
    indent = None
    ports_inline = None
    in_resources = False
    res_indent = None
    res_section = None  # 'limits' or 'requests'
    dep["resources"] = {}
    dep["env"] = {}
    dep["namespace"] = None
    dep["service"] = {"type": "NodePort"}
    dep["ingress_hosts"] = []
    dep["volumes"] = []
    with open(path, 'r') as f:
        for raw in f:
            line = raw.rstrip('\n')
            if not line.strip() or line.strip().startswith('#'):
                continue
            if line.startswith('deployment:'):
                in_dep = True
                indent = None
                in_resources = False
                continue
            if not in_dep:
                continue
            m = re.match(r"^(\s+)(\S.*)$", line)
            if not m:
                # end of block
                in_dep = False
                in_resources = False
                continue
            sp, content = m.group(1), m.group(2)
            if indent is None:
                indent = len(sp)
            if len(sp) < indent:
                in_dep = False
                in_resources = False
                continue
            # replicas: N
            r = re.match(r"^replicas\s*:\s*(\d+)\s*$", content)
            if r:
                dep["replicas"] = int(r.group(1))
                continue
            # ports: [a, b]
            p = re.match(r"^ports\s*:\s*\[(.*)\]\s*$", content)
            if p:
                items = [x.strip() for x in p.group(1).split(',') if x.strip()]
                dep["ports"] = [int(x) for x in items]
                ports_inline = True
                continue
            # ports: (multi line)
            if content.startswith('ports:'):
                dep["ports"] = []
                ports_inline = False
                continue
            if ports_inline is False:
                it = re.match(r"^\s*-\s*(\d+)\s*$", content)
                if it:
                    dep["ports"].append(int(it.group(1)))
                    continue
            # resources:
            if content.startswith('resources:'):
                dep["resources"] = {}
                in_resources = True
                res_indent = len(sp)
                res_section = None
                continue
            if in_resources:
                # detect sections limits/requests
                if len(sp) <= res_indent:
                    in_resources = False
                    res_section = None
                    continue
                sec = re.match(r"^(limits|requests)\s*:\s*$", content)
                if sec:
                    res_section = sec.group(1)
                    dep["resources"].setdefault(res_section, {})
                    continue
                kv = re.match(r"^(\w+)\s*:\s*(\S+)\s*$", content)
                if kv and res_section:
                    k, v = kv.group(1), kv.group(2)
                    dep["resources"].setdefault(res_section, {})[k] = v
                    continue
            # env:
            if content.startswith('env:'):
                dep["env"] = {}
                env_indent = len(sp)
                continue
            if isinstance(dep.get("env"), dict) and 'env_indent' in locals():
                # end of env block
                if len(sp) < env_indent:
                    del env_indent
                else:
                    kv = re.match(r"^(\w+)\s*:\s*(.*)\s*$", content)
                    if kv:
                        k, v = kv.group(1), kv.group(2)
                        dep["env"][k] = v
                        continue
            # namespace:
            nsm = re.match(r"^namespace\s*:\s*(\S+)\s*$", content)
            if nsm:
                dep["namespace"] = nsm.group(1)
                continue
            # service:
            if content.startswith('service:'):
                service_indent = len(sp)
                dep["service"] = dep.get("service", {"type": "NodePort"})
                continue
            if 'service_indent' in locals():
                if len(sp) < service_indent:
                    del service_indent
                else:
                    st = re.match(r"^type\s*:\s*(\w+)\s*$", content)
                    if st:
                        dep["service"]["type"] = st.group(1)
                        continue
            # ingress:
            if content.startswith('ingress:'):
                ing_indent = len(sp)
                dep["ingress_hosts"] = []
                continue
            if 'ing_indent' in locals():
                if len(sp) < ing_indent:
                    del ing_indent
                else:
                    ih_inline = re.match(r"^hosts\s*:\s*\[(.*)\]\s*$", content)
                    if ih_inline:
                        items = [x.strip() for x in ih_inline.group(1).split(',') if x.strip()]
                        dep["ingress_hosts"].extend(items)
                        continue
                    if content.startswith('hosts:'):
                        # expect list items next lines
                        hosts_indent = len(sp)
                        continue
                    if 'hosts_indent' in locals():
                        if len(sp) <= hosts_indent:
                            del hosts_indent
                        else:
                            it = re.match(r"^\s*-\s*(\S+)\s*$", content)
                            if it:
                                dep["ingress_hosts"].append(it.group(1))
                                continue
            # volumes:
            if content.startswith('volumes:'):
                vols_indent = len(sp)
                current = None
                continue
            if 'vols_indent' in locals():
                if len(sp) < vols_indent:
                    del vols_indent
                    current = None
                else:
                    item = re.match(r"^\-\s*name\s*:\s*(\S+)\s*$", content)
                    if item:
                        current = {"name": item.group(1)}
                        dep["volumes"].append(current)
                        continue
                    if current is not None:
                        kv = re.match(r"^(claimName|mountPath|subPath|readOnly)\s*:\s*(\S+)\s*$", content)
                        if kv:
                            k, v = kv.group(1), kv.group(2)
                            if k == 'readOnly':
                                current[k] = v.lower() in ('true','1','yes')
                            else:
                                current[k] = v
                            continue
    return data


def k8s_yaml(app: str, image: str, replicas: int,
             ports: List[int], resources: Dict, env: Dict,
             namespace: str | None,
             service_type: str,
             ingress_hosts: List[str],
             volumes: List[Dict]) -> Tuple[str, str]:
    # Deployment YAML
    cports = "\n".join(
        [f"        - containerPort: {p}" for p in ports])
    env_lines: List[str] = []
    if env:
        env_lines.append('        env:')
        for k, v in env.items():
            env_lines.append(f"        - name: {k}")
            env_lines.append(f"          value: \"{v}\"")
    # resources block
    res_lines: List[str] = []
    if resources:
        if resources.get('limits') or resources.get('requests'):
            res_lines.append('        resources:')
            if resources.get('limits'):
                res_lines.append('          limits:')
                for k, v in resources['limits'].items():
                    res_lines.append(f"            {k}: {v}")
            if resources.get('requests'):
                res_lines.append('          requests:')
                for k, v in resources['requests'].items():
                    res_lines.append(f"            {k}: {v}")

    # volumes and mounts
    vmount_lines: List[str] = []
    vdecl_lines: List[str] = []
    if volumes:
        vmount_lines.append('        volumeMounts:')
        for v in volumes:
            name = v.get('name')
            mpath = v.get('mountPath')
            if not name or not mpath:
                continue
            vmount_lines.append(f"        - name: {name}")
            vmount_lines.append(f"          mountPath: {mpath}")
            if v.get('subPath'):
                vmount_lines.append(f"          subPath: {v['subPath']}")
            if v.get('readOnly'):
                vmount_lines.append("          readOnly: true")
        vdecl_lines.append('      volumes:')
        for v in volumes:
            name = v.get('name')
            claim = v.get('claimName')
            if not name or not claim:
                continue
            vdecl_lines.append(f"      - name: {name}")
            vdecl_lines.append("        persistentVolumeClaim:")
            vdecl_lines.append(f"          claimName: {claim}")

    ns_meta = f"\n  namespace: {namespace}" if namespace else ""
    d = [
        "apiVersion: apps/v1",
        "kind: Deployment",
        f"metadata:\n  name: {app}{ns_meta}",
        "spec:",
        f"  replicas: {replicas}",
        "  selector:",
        f"    matchLabels:\n      app: {app}",
        "  template:",
        "    metadata:",
        f"      labels:\n        app: {app}",
        "    spec:",
        "      containers:",
        f"      - name: {app}",
        f"        image: {image}",
        ("        ports:\n" + cports) if ports else "",
        "\n".join(env_lines) if env_lines else "",
        "\n".join(res_lines) if res_lines else "",
        "\n".join(vmount_lines) if vmount_lines else "",
        "\n".join(vdecl_lines) if vdecl_lines else "",
    ]
    deploy_yaml = "\n".join([x for x in d if x != ""]) + "\n"

    # Service YAML (NodePort to reach from outside)
    sports = []
    for i, p in enumerate(ports):
        sports.append("  - name: p%d" % i)
        sports.append(f"    port: {p}")
        sports.append(f"    targetPort: {p}")
        sports.append("    protocol: TCP")
    s = [
        "apiVersion: v1",
        "kind: Service",
        f"metadata:\n  name: {app}{ns_meta}",
        "spec:",
        f"  type: {service_type}",
        f"  selector:\n    app: {app}",
        "  ports:",
        "\n".join(sports) if sports else "",
    ]
    svc_yaml = "\n".join([x for x in s if x != ""]) + "\n"

    ing_yaml = ""
    if ingress_hosts:
        rules_lines: List[str] = []
        for h in ingress_hosts:
            rules_lines.append(f"  - host: {h}")
            rules_lines.append("    http:")
            rules_lines.append("      paths:")
            rules_lines.append("      - path: /")
            rules_lines.append("        pathType: Prefix")
            rules_lines.append("        backend:")
            rules_lines.append("          service:")
            rules_lines.append(f"            name: {app}")
            rules_lines.append("            port:")
            p0 = ports[0] if ports else 80
            rules_lines.append(f"              number: {p0}")
        ing = [
            "apiVersion: networking.k8s.io/v1",
            "kind: Ingress",
            f"metadata:\n  name: {app}{ns_meta}\n  annotations:\n    kubernetes.io/ingress.class: traefik",
            "spec:",
            "  rules:",
            "\n".join(rules_lines),
        ]
        ing_yaml = "\n".join(ing) + "\n"

    return deploy_yaml, svc_yaml + ("---\n" + ing_yaml if ing_yaml else "")


def main(argv: List[str]) -> int:
    if len(argv) < 2:
        print("Usage: whanos_k8s_gen.py <whanos.yml> [image] [--name NAME]",
              file=sys.stderr)
        return 84
    ypath = argv[1]
    image = "app:latest"
    name_override: str | None = None
    i = 2
    while i < len(argv):
        a = argv[i]
        if a == '--name' and i + 1 < len(argv):
            name_override = argv[i + 1]
            i += 2
            continue
        elif not a.startswith('-') and image == "app:latest":
            image = a
        i += 1
    if not os.path.isfile(ypath):
        print("Error: whanos.yml not found", file=sys.stderr)
        return 84
    conf = parse_whanos_yml(ypath)
    dep = conf.get("deployment", {})
    replicas = int(dep.get("replicas", 1))
    ports = dep.get("ports", [])
    app = name_override or os.path.basename(os.getcwd())
    d, s = k8s_yaml(app, image, replicas, ports,
                    dep.get("resources", {}), dep.get("env", {}),
                    dep.get("namespace") or None,
                    dep.get("service", {}).get("type", "NodePort"),
                    dep.get("ingress_hosts", []),
                    dep.get("volumes", []))
    sys.stdout.write("---\n")
    sys.stdout.write(d)
    sys.stdout.write("---\n")
    sys.stdout.write(s)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
