#include "QMC_Algorithm.h"

QMC_Algorithm::QMC_Algorithm(int n, int m, int d, int arr[])
{
    this->n = n;
    this->m = m;
    this->d = d;

    if (n < 1 || n > MAX_VAR_N || m < 1 || d < 0 || (m + d) > MAX_ITM_N)
    {
        printf("--------------------------Error1--------------------------\n");
    }

    input = (int *)calloc(m + d, sizeof(int));

    term_len = sizeof(int) + sizeof(char) * (n + 1) + sizeof(int) * (m + d) * 2;
    group_len = sizeof(int) + term_len * (m + d) * (m + d);

    temp = (char *)calloc(group_len * (n + 1), sizeof(char));
    output = (char *)calloc(group_len * (n + 1), sizeof(char));

    if (!temp || !input || !output)
    {
        printf("--------------------------Error2--------------------------\n");

        free(temp);
        free(input);
        free(output);
    }

    for (int i = 0; i < m + d; i++)
    {
        input[i] = arr[i];
        // cout << arr[i] << ", ";

        if (input[i] >= (0x01 << n))
        {
            printf("--------------------------Error3--------------------------\n");

            free(temp);
            free(input);
            free(output);
        }
    }
    cout << endl;

    load_data();
    while (combine_terms());
    while (find_prime());

    show_output();

    free(temp);
    free(input);
    free(output);

}

void QMC_Algorithm::load_data()
{
    for (int g = 0; g <= n; g++) {
        for (int i = 0; i < m + d; i++) {
            int bits = 0;
            int temp = input[i];

            while (temp) {
                if (temp & 0x01) {
                    bits++;
                }

                temp >>= 1;
            }

            if (bits == g) {
                int temp = input[i];
                int term = TERM_NUM(output, g);

                for (int k = 0; k < n; k++) {
                    TERM_DATA(output, g, term, k) = (temp & (0x01 << (n - 1))) ? '1' : '0';

                    temp <<= 1;
                }

                TERM_NUM(output, g)++;
                TERM_DATA(output, g, term, n) = 'm';

                SUB_NUM(output, g, term)++;
                SUB_DATA(output, g, term, 0) = input[i];
            }
        }
    }
}

void QMC_Algorithm::copy_terms()
{
    for (int g = 0; g <= n; g++) {
        for (int t = 0; t < TERM_NUM(output, g); t++) {
            if (TERM_DATA(output, g, t, n) == '*') {
                continue;
            }

            memcpy(TERM_PTR(temp, g, TERM_NUM(temp, g)++), TERM_PTR(output, g, t), term_len);
        }
    }

    memcpy(output, temp, group_len * (n + 1));
}

int QMC_Algorithm::combine_terms()
{
    int loop = 0;

    memset(temp, 0x00, group_len * (n + 1));

    // combine two terms into one term
    for (int g = 0; g < n; g++) {
        for (int t0 = 0; t0 < TERM_NUM(output, g); t0++) {
            for (int t1 = 0; t1 < TERM_NUM(output, g + 1); t1++) {
                int p = 0, diff = 0;

                for (int k = 0; k < n; k++) {
                    if (TERM_DATA(output, g, t0, k) != TERM_DATA(output, g + 1, t1, k)) {
                        p = k, diff++;
                    }
                }

                if (diff == 1) {
                    int term = TERM_NUM(temp, g);

                    for (int i = 0; i < SUB_NUM(output, g, t0); i++) {
                        SUB_DATA(temp, g, term, SUB_NUM(temp, g, term)++) = SUB_DATA(output, g, t0, i);
                    }

                    for (int i = 0; i < SUB_NUM(output, g + 1, t1); i++) {
                        SUB_DATA(temp, g, term, SUB_NUM(temp, g, term)++) = SUB_DATA(output, g + 1, t1, i);
                    }

                    sort(SUB_PDATA(temp, g, term), SUB_PDATA(temp, g, term) + SUB_NUM(temp, g, term));

                    int *ret = unique(SUB_PDATA(temp, g, term), SUB_PDATA(temp, g, term) + SUB_NUM(temp, g, term));
                    SUB_NUM(temp, g, term) = ret - SUB_PDATA(temp, g, term);

                    memcpy(TERM_PDATA(temp, g, term), TERM_PDATA(output, g, t0), n + 1);
                    TERM_DATA(temp, g, term, p) = '-';
                    TERM_DATA(temp, g, term, n) = 'm';
                    TERM_NUM(temp, g)++;

                    TERM_DATA(output, g, t0, n) = '*';
                    TERM_DATA(output, g + 1, t1, n) = '*';

                    loop = 1;
                }
            }
        }
    }

    copy_terms();

    memset(temp, 0x00, group_len * (n + 1));

    // remove duplicate terms
    for (int g = 0; g <= n; g++) {
        for (int t0 = 0; t0 < TERM_NUM(output, g) - 1; t0++) {
            for (int t1 = t0 + 1; t1 < TERM_NUM(output, g); t1++) {
                if (!memcmp(TERM_PDATA(output, g, t0), TERM_PDATA(output, g, t1), n)) {
                    for (int k = 0; k < SUB_NUM(output, g, t1); k++) {
                        SUB_DATA(output, g, t0, SUB_NUM(output, g, t0)++) = SUB_DATA(output, g, t1, k);
                    }

                    sort(SUB_PDATA(output, g, t0), SUB_PDATA(output, g, t0) + SUB_NUM(output, g, t0));

                    int *ret = unique(SUB_PDATA(output, g, t0), SUB_PDATA(output, g, t0) + SUB_NUM(output, g, t0));
                    SUB_NUM(output, g, t0) = ret - SUB_PDATA(output, g, t0);

                    TERM_DATA(output, g, t1, n) = '*';
                }
            }
        }
    }

    copy_terms();

    return loop;
}

int QMC_Algorithm::find_prime()
{
    int loop = 0;
    int term = 0, group = 0;
    int count = 0, max_count = 0;

    // find the term that contains a single minterm
    for (int i = 0; i < m; i++)
    {
        count = 0;

        for (int g = 0; g <= n; g++)
        {
            for (int t = 0; t < TERM_NUM(output, g); t++)
            {
                for (int k = 0; k < SUB_NUM(output, g, t); k++)
                {
                    if (input[i] == SUB_DATA(output, g, t, k))
                    {
                        count++;

                        term = t;
                        group = g;
                    }
                }
            }
        }

        if (count == 1)
        {
            TERM_DATA(output, group, term, n) = 'x';

            for (int k0 = 0; k0 < SUB_NUM(output, group, term); k0++)
            {
                int found = SUB_DATA(output, group, term, k0);

                for (int g = 0; g <= n; g++)
                {
                    for (int t = 0; t < TERM_NUM(output, g); t++)
                    {
                        for (int k1 = 0; k1 < SUB_NUM(output, g, t); k1++)
                        {
                            if (found == SUB_DATA(output, g, t, k1))
                            {
                                SUB_DATA(output, g, t, k1) = -1;
                            }
                        }
                    }
                }
            }

            loop = 1;
        }
    }

    // find the term that contains most minterms
    for (int g = 0; g <= n; g++)
    {
        for (int t = 0; t < TERM_NUM(output, g); t++)
        {
            count = 0;

            for (int k = 0; k < SUB_NUM(output, g, t); k++)
            {
                for (int i = 0; i < m; i++)
                {
                    if (input[i] == SUB_DATA(output, g, t, k))
                    {
                        count++;

                        if (max_count < count)
                        {
                            max_count = count;

                            term = t;
                            group = g;
                        }
                    }
                }
            }
        }
    }

    if (max_count != 0)
    {
        TERM_DATA(output, group, term, n) = 'x';

        for (int k0 = 0; k0 < SUB_NUM(output, group, term); k0++)
        {
            int found = SUB_DATA(output, group, term, k0);

            for (int g = 0; g <= n; g++)
            {
                for (int t = 0; t < TERM_NUM(output, g); t++)
                {
                    for (int k1 = 0; k1 < SUB_NUM(output, g, t); k1++)
                    {
                        if (found == SUB_DATA(output, g, t, k1))
                        {
                            SUB_DATA(output, g, t, k1) = -1;
                        }
                    }
                }
            }
        }

        loop = 1;
    }

    return loop;
}

void QMC_Algorithm::show_output()
{
    int count = 0;

    for (int g = 0; g <= n; g++)
    {
        for (int t = 0; t < TERM_NUM(output, g); t++)
        {
            if (TERM_DATA(output, g, t, n) == 'x')
            {
                if (!count)
                {
                    printf("    SOP = ");
                }
                else
                {
                    printf(" + ");
                }

                for (int k = 0; k < n; k++)
                {
                    if (!TERM_DATA(output, g, t, k))
                    {
                        break;
                    }

                    if (TERM_DATA(output, g, t, k) != '-')
                    {
                        count++;

                        printf("%c%s", 'A' + k, TERM_DATA(output, g, t, k) == '1' ? "" : "'");
                    }
                }
            }
        }
    }

    if (!count)
    {
        printf("1");
    }

    printf("\n");
}
