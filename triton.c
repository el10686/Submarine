#include <stdio.h>
#include <stdlib.h>
#define hash 1000000103

int main() {

	int n, m, k, x, s, e;

	scanf("%d %d %d %d", &n, &m, &k, &x);

	int ***count = malloc(sizeof(int **) * n);
	for(int i = 0; i < n; i++) {
		count[i] = malloc(sizeof(int *) * m);
		for (int j = 0; j < m ; j++)
			count[i][j] = malloc(sizeof(int) * k + 1);
	}

	int **pilot_info = malloc(k * sizeof(int *));
	for (int i=0; i<=k; i++)
		pilot_info[i] = malloc(4 * sizeof(int));

	int **pilot_grid = malloc(n * sizeof(int *));
	for (int i=0; i<n; i++)
		pilot_grid[i] = malloc(m * sizeof(int));

	//arxikopoihse to grid twn pilotikwn me -1 kai ton 3d me 0
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++) {
			pilot_grid[i][j] = -1;
			for(int l = 0; l <= k; l++)
				count[i][j][l] = 0;
		}

	//apo8ikeuse ta stoixeia twn pilotikwn kai ftia3e to grid tous vazontas to i gia id tis ka8e diavasis
	for(int i = 0; i < k; i++) {
		scanf("%d %d", &s, &e);
		pilot_info[i][0] = s / m;
		pilot_info[i][1] = s % m;
		pilot_info[i][2] = e / m;
		pilot_info[i][3] = e % m;
		pilot_grid[s / m][s % m] = i;
		pilot_grid[e / m][e % m] = i;
	}

	//ftiaxe th m-1 stili
	for(int i = n - 1; i >= 0; i--) {
		//eimai to koutaki n-1, m-1
		if(i == n - 1)
			count[i][m - 1][0] = 1;
		else {
			//koita an anoiko se diavasi kai eimai telos
			if((pilot_grid[i][m - 1] != -1)
					&& (i == pilot_info[pilot_grid[i][m - 1]][2])
					&& (m - 1 == pilot_info[pilot_grid[i][m - 1]][3])) {
				//an nai vres tin arxi mou
				int s_x = pilot_info[pilot_grid[i][m - 1]][0];
				int s_y = pilot_info[pilot_grid[i][m - 1]][1];

				//vres to teleutaio epiepdo opou den exw 0
				int index = 0;
				for(int l = 0; l <= k; l++)
					if(count[s_x][s_y][l] != 0)
						index = l;
				//vale sto index + 1 to 1
				count[i][m - 1][index + 1] = 1;
			}
			//eite eimai arxi diavasis eite kanoniko koutaki
			else {
				//an to proigoumeno kouti einai arxi diavasis proxora sto panw kouti
				if((pilot_grid[i + 1][m - 1] != -1)
						&& (i + 1 == pilot_info[pilot_grid[i + 1][m - 1]][0])
						&& (m - 1 == pilot_info[pilot_grid[i + 1][m - 1]][1]))
					continue;
				else
					for (int l = 0; l <= k; l++)
						//alliws vale se ola ta epipeda k tis times toy apo katw koutiou
						count[i][m - 1][l] = count[i + 1][m - 1][l];
			}
		}
	}

	//ftia3e thn n-1 grammi
	for(int j = m - 1; j >= 0; j--) {
		//eimai to koutaki n-1, m-1
		if(j == m - 1)
			count[n - 1][j][0] = 1;
		else {
			//koita an anoiko se diavasi kai eimai telos
			if((pilot_grid[n - 1][j] != -1)
					&& (n - 1 == pilot_info[pilot_grid[n - 1][j]][2])
					&& (j == pilot_info[pilot_grid[n - 1][j]][3])) {
				//an nai vres tin arxh mou
				int s_x = pilot_info[pilot_grid[n - 1][j]][0];
				int s_y = pilot_info[pilot_grid[n - 1][j]][1];

				//vres to teleutaio epipedo opou den exw 0
				int index = 0;
				for (int l = 0; l <= k; l++)
					if (count[s_x][s_y][l] != 0)
						index = l;
				//valse sto index + 1 to 1
				count[n - 1][j][index + 1] = 1;

			}
			//eite eimai arxi diavasis eite kanoniko kouti
			else {
				//an to proigoumeno kouti einai arxi diavasis proxora sto aristero kouti
				if((pilot_grid[n - 1][j + 1] != -1)
						&& (n - 1 == pilot_info[pilot_grid[n - 1][j + 1]][0])
						&& (j + 1 == pilot_info[pilot_grid[n - 1][j + 1]][1]))
					continue;
				else
					for (int l = 0; l <= k; l++)
						//alliws vale se ola ta epipeda k tis times tou de3iou koutiou
						count[n - 1][j][l] = count[n - 1][j + 1][l];
			}
		}
	}

	//ftia3e to upoloipo grid
	for(int i = n - 2; i >= 0; i--) {
		for (int j = m - 2; j >= 0; j--) {
			//eimai telos pilotikis diastasis
			if ((pilot_grid[i][j] != -1)
					&& (i == pilot_info[pilot_grid[i][j]][2])
					&& (j == pilot_info[pilot_grid[i][j]][3])) {
				int s_x = pilot_info[pilot_grid[i][j]][0];
				int s_y = pilot_info[pilot_grid[i][j]][1];
				for (int l = 0; l <= k; l++)
					//gia ola ta k ektos tou k = 0 vale tis times tous sta k + 1 mou
					if(l != 0)
						count[i][j][l] = (count[i][j][l] % hash + count[s_x][s_y][l - 1] % hash) % hash;
			}
			//kai oi 2 geitones mou einai arxi pilotikis diavasis
			if ((pilot_grid[i][j + 1] != -1)
					&& (pilot_grid[i + 1][j] != -1)
					&& (i == pilot_info[pilot_grid[i][j + 1]][0])
					&& (j + 1 == pilot_info[pilot_grid[i][j + 1]][1])
					&& (i + 1 == pilot_info[pilot_grid[i + 1][j]][0])
					&& (j == pilot_info[pilot_grid[i + 1][j]][1]))
				//mhn prostheseis tipota
				continue;
			//o de3is mou geitonas einai arxi pilotikis
			else if((pilot_grid[i][j + 1] != -1)
					&& (i == pilot_info[pilot_grid[i][j + 1]][0])
					&& (j + 1 == pilot_info[pilot_grid[i][j + 1]][1]))
				//prosthese gia ola ta k tou apo katw moy sta dika moy k
				for (int l = 0; l <= k; l++)
					count[i][j][l] = (count[i][j][l] % hash + count[i+1][j][l] % hash) % hash ;
			//o apo katw geitonas einai arxi pilotikis
			else if((pilot_grid[i + 1][j] != -1)
					&& (i + 1 == pilot_info[pilot_grid[i + 1][j]][0])
					&& (j == pilot_info[pilot_grid[i + 1][j]][1]))
				//prosthese gia ola ta k tou de3ia moy sta dika moy k
				for (int l = 0; l <= k; l++)
					count[i][j][l] = (count[i][j][l] % hash + count[i][j + 1][l] % hash) % hash ;
			//oi geitones mou einai kanonika koutia h telh pilotikwn
			else
				for (int l = 0; l <= k; l++) {
					count[i][j][l] = (count[i][j][l] % hash + count[i][j + 1][l] % hash) % hash ;
					count[i][j][l] = (count[i][j][l] % hash + count[i + 1][j][l] % hash) % hash ;
				}
		}
	}

	int sum = 0;
	for(int i = 0; i <= x; i++)
		sum = (sum % hash + count[0][0][i] % hash) % hash;

	printf("%d\n", sum % hash);

	return 0;
}
