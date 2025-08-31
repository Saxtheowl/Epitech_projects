/*
** EPITECH PROJECT, 2025
** FASTAtools
** File description:
** Additional tests
*/

#include <criterion/criterion.h>
#include <string.h>
#include "fastatools.h"

Test(fasta, parse_multiline_sequence)
{
    const char *raw = ">seq1\nACG\nTTA\n>seq2\nGG\n";
    fasta_entry_t *e; int n;
    cr_assert(parse_fasta(raw, &e, &n));
    cr_assert_eq(n, 2);
    cr_assert_str_eq(e[0].seq, "ACGTTA");
    cr_assert_str_eq(e[1].header, "seq2");
    free_fasta(e, n);
}

Test(fasta, revcomp_maps_unknown)
{
    /* lowercases and unknown bases map to N */
    char *rc = revcomp("aXcU");
    cr_assert_str_eq(rc, "ANGT");
    free(rc);
}

