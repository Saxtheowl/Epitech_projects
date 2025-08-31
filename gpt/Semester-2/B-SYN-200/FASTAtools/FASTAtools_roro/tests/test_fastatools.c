/*
** EPITECH PROJECT, 2025
** FASTAtools
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "fastatools.h"

Test(fasta, revcomp_basic)
{
    char *rc = revcomp("ACGT");
    cr_assert_str_eq(rc, "ACGT");
    free(rc);
}

Test(fasta, parse)
{
    const char *raw = ">seq1\nACGT\n>seq2\nTT\n";
    fasta_entry_t *e; int n;
    cr_assert(parse_fasta(raw, &e, &n));
    cr_assert_eq(n, 2);
    cr_assert_str_eq(e[0].header, "seq1");
    cr_assert_str_eq(e[1].seq, "TT");
    free_fasta(e, n);
}

