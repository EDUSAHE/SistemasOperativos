#include <stdio.h>

int main() {
    int i, j, k, n, m;
    int alloc[10][10], max[10][10], avail[10];
    int f[10], ans[10], index = 0;

    printf("Ingrese el número de procesos: ");
    scanf("%d", &n);
    printf("Ingrese el número de tipos de recursos: ");
    scanf("%d", &m);

    for (i = 0; i < n; i++) {
        f[i] = 0;
        printf("Ingrese los recursos asignados para el proceso %d: ", i + 1);
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    for (i = 0; i < n; i++) {
        printf("Ingrese los recursos máximos necesarios para el proceso %d: ", i + 1);
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Ingrese el número de recursos disponibles: ");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (max[i][j] - alloc[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[index++] = i;
                    for (int y = 0; y < m; y++) {
                        avail[y] += alloc[i][j];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    printf("La secuencia segura es: ");
    for (i = 0; i < n - 1; i++) {
        printf("P%d -> ", ans[i] + 1);
    }
    printf("P%d\n", ans[n - 1] + 1);

    return 0;
}