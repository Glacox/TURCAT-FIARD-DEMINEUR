// Demineur TURCAT Fiard.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define BOMB 10
#define tableiSize 10
#define VIDE 15
#define FLAG 11

#define BLK   "\x1B[30m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define WHTB   "\x1B[47m"
#define RESET "\x1B[0m"



// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.


int index(int x, int y, int ligne)
{
    int pos = y * ligne + x;
    return pos;
}
void discover(int* playground, int* t, int ligne, int x, int y)
{
    int pos = index(x, y, ligne);
    if (playground[pos] == VIDE)
    {
        t[pos] = 0;
        playground[pos] = 0;
        //printf("%d,%d", x, y);
        //right
        if (x + 1 < ligne)
        {
            discover(playground, t, ligne, x + 1, y);
        }
        //left
        if (x - 1 >= 0)
        {
            discover(playground, t, ligne, x - 1, y);
        }
        //down
        if (y + 1 < ligne)
        {
            discover(playground, t, ligne, x, y + 1);
        }
        //up
        if (y - 1 >= 0)
        {
            discover(playground, t, ligne, x, y - 1);
        }
        //up right
        if (x + 1 < ligne and y - 1 >= 0)
        {
            discover(playground, t, ligne, x + 1, y - 1);
        }
        //down left
        if (x - 1 >= 0 and y + 1 < ligne)
        {
            discover(playground, t, ligne, x - 1, y + 1);
        }
        //down right
        if (x + 1 < ligne and y + 1 < ligne)
        {
            discover(playground, t, ligne, x + 1, y + 1);
        }
        //up left
        if (x - 1 >= 0 and y - 1 >= 0)
        {
            discover(playground, t, ligne, x - 1, y - 1);
        }
    }
    if (playground[pos] == 10) {
        t[pos] = t[pos];
    }
    else
    {
        t[pos] = playground[pos];
    }


}
bool play(int* playground, int* t, int ligne)
{

    int x, y;
    int flag;
    printf("Colonne \n");
    scanf_s("%d", &x);
    if (x < 0) {
        printf("Vous essayer de jouer en dehors du tableau\n");
        play(playground, t, ligne);
    }
    else if (x >= ligne) {
        printf("Vous essayer de jouer en dehors du tableau\n");
        play(playground, t, ligne);
    }
    printf("Ligne \n");
    scanf_s("%d", &y);
    if (y < 0) {
        printf("Vous essayer de jouer en dehors du tableau\n");
        play(playground, t, ligne);
    }
    else if (y >= ligne) {
        printf("Vous essayer de jouer en dehors du tableau\n");
        play(playground, t, ligne);
    }
    printf("Placer un drapeau (y(1)/n(0)\n");
    scanf_s("%d", &flag);
    if (flag != 0 && flag != 1) {
        printf("1 = placer un drapeau ,0 = creuser la case\n");
        play(playground, t, ligne);
    }

    int pos = index(x, y, ligne);
    if (x >= 0 and x < ligne and y >= 0 and y < ligne) {
        if (flag == 1)
        {
            playground[pos] == FLAG;
            t[pos] = FLAG;
        }
        if (flag == 0)
        {
            if (playground[pos] == 10)
            {
                t[pos] = playground[pos];
                return true;
            }
            else
            {
                discover(playground, t, ligne, x, y);
                return false;
            }
        }
    }






}

bool winCondition(int* t, int* playground, int ligne, int bombNumber) {
    //win check
    int winCount = 0;
    for (int i = 0; i < ligne; ++i)
    {
        for (int m = 0; m < ligne; m++) {
            int pos2 = index(i, m, ligne);
            if (t[pos2] != VIDE and t[pos2] != BOMB and t[pos2] != FLAG) {
                ++winCount;
            }
        }
    }


    if (winCount == (ligne * ligne) - bombNumber) {
        return true;
    }
    else {
        return false;
    }
}


int countVerif(int x, int y, int ligne, int* playground)
{
    int count = 0;
    int pos = index(x, y, ligne);
    //up
    if (playground[pos] == BOMB)
        return 0;

    if (y - 1 >= 0)
    {
        int up = index(x, y - 1, ligne);
        if (playground[up] == BOMB)
        {
            ++count;
        }
    }
    //printf(" %d ", up);
    //down
    if (y + 1 < ligne)
    {
        int down = index(x, y + 1, ligne);
        if (playground[down] == BOMB)
        {
            ++count;
        }
    }
    //printf(" %d ", down);
    //right
    if (x + 1 < ligne)
    {
        int right = index(x + 1, y, ligne);
        if (playground[right] == BOMB)
        {
            ++count;
        }
    }
    //printf(" %d ", right);
    //left
    if (x - 1 >= 0)
    {
        int left = index(x - 1, y, ligne);
        if (playground[left] == BOMB)
        {
            ++count;
        }
    }
    //printf(" %d ", left);
    //up right
    if (x + 1 < ligne and y - 1 >= 0)
    {
        int ur = index(x + 1, y - 1, ligne);
        if (playground[ur] == BOMB)
        {
            ++count;
        }
    }
    //printf(" %d ", ur);
    //up left
    if (x - 1 >= 0 and y - 1 >= 0)
    {
        int ul = index(x - 1, y - 1, ligne);
        if (playground[ul] == BOMB)
        {
            ++count;
        }
    }
    //printf(" %d ", ul);
    //down right
    if (x + 1 < ligne and y + 1 < ligne)
    {
        int dr = index(x + 1, y + 1, ligne);
        if (playground[dr] == BOMB)
        {
            ++count;
        }
    }
    //printf(" %d ", dr);
    //down left
    if (x - 1 >= 0 and y + 1 < ligne)
    {
        int dl = index(x - 1, y + 1, ligne);
        if (playground[dl] == BOMB)
        {
            ++count;
        }
    }
    //printf(" %d ", dl);
    if (count == 0)
    {
        playground[pos] = playground[pos];
    }
    else
    {
        playground[pos] = count;
    }
    return count;

}

void bombPlacement(int* playground, int bombNumber, int ligne) {
    srand(time(NULL));
    for (int l = 0; l < bombNumber; ++l) {
        int rBombs = rand() % (ligne * ligne) + 1;
        playground[rBombs] = 10;
    }
}
void countgrid(int* playground, int ligne)
{
    for (int o = 0; o < ligne; ++o)
    {
        for (int p = 0; p < ligne; ++p)
        {
            countVerif(p, o, ligne, playground);
        }
    }
}


void visualRender(int* t, int p, int ligne)
{
    printf("   ");
    for (int m = 0; m < ligne; ++m)
    {
        if (m < 9) {
            printf("  %d", m);
        }
        if (m == 9) {
            printf("  %d ", m);
        }
        if (m >= 10) {
            printf(" %d", m);
        }
    }
    for (int i = 0; i < ligne; ++i) {
        printf("\n");
        if (i < 10) {
            printf(" %d  ", i);
        }
        if (i >= 10) {
            printf(" %d ", i);
        }
        for (int n = 0; n < ligne; ++n) {
            if (t[p] == 0) {
                printf("[" WHTB " " RESET "]");
            }
            else if (t[p] == 1) {
                printf("[" BLU "1" RESET "]");
            }
            else if (t[p] == 2) {
                printf("[" GRN "2" RESET "]");
            }
            else if (t[p] == 3) {
                printf("[" RED "3" RESET "]");
            }
            else if (t[p] == 4) {
                printf("[" MAG "4" RESET "]");
            }
            else if (t[p] == 5) {
                printf("[" YEL "5" RESET "]");
            }
            else if (t[p] == 6) {
                printf("[" CYN "6" RESET "]");
            }
            else if (t[p] == 7) {
                printf("[" WHT "7" RESET "]");
            }
            else if (t[p] == 8) {
                printf("[" WHT "8" RESET "]");
            }
            else if (t[p] == BOMB) {
                printf("[@]");
            }
            else if (t[p] == FLAG) {
                printf("[" RED "P" RESET "]");
            }
            else if (t[p] == VIDE) {
                printf("[ ]");
            }
            ++p;
        }
        printf("\n");
    }
}


int main()
{
    int iSize, ligne, bombNumber;
    printf("combien de ligne?\n");
    scanf_s("%d", &ligne);
    iSize = ligne * ligne;
    int* tab = (int*)malloc(sizeof(int) * iSize);
    for (int a = 0; a < iSize; ++a) {
        *(tab + a) = VIDE;
    }

    int* playground = (int*)malloc(sizeof(int) * iSize);
    for (int b = 0; b < iSize; ++b) {
        *(playground + b) = VIDE;
    }
    printf("combien de bomb");
    scanf_s("%d", &bombNumber);
    int winCount = 0;
    bool lose = false;
    bool win = false;
    int p = 0;
    int count = 0;
    bombPlacement(playground, bombNumber, ligne);
    countgrid(playground, ligne);


    while (lose == false and winCondition(tab, playground, ligne, bombNumber) == false) {
        printf("\n");
        visualRender(tab, p, ligne);
        if (play(playground, tab, ligne) == true) {
            lose = true;
        }
    }
    if (lose == true) {
        visualRender(tab, p, ligne);
        printf(RED ":::   :::  ::::::::  :::    :::       ::::::::: ::::::::::: :::::::::: :::::::::  \n:+:   :+: :+:    :+: :+:    :+:       :+:    :+:    :+:     :+:        :+:    :+: \n +:+ +:+  +:+    +:+ +:+    +:+       +:+    +:+    +:+     +:+        +:+    +:+ \n  +#++:   +#+    +:+ +#+    +:+       +#+    +:+    +#+     +#++:++#   +#+    +:+ \n   +#+    +#+    +#+ +#+    +#+       +#+    +#+    +#+     +#+        +#+    +#+ \n   #+#    #+#    #+# #+#    #+#       #+#    #+#    #+#     #+#        #+#    #+# \n   ###     ########   ########        ######### ########### ########## #########  \n" RESET);
        free(tab);
    }
    if (winCondition(tab, playground, ligne, bombNumber) == true) {
        visualRender(tab, p, ligne);
        printf(GRN ":::   :::  ::::::::  :::    :::       :::       ::: ::::::::::: ::::    ::: \n:+:   :+: :+:    :+: :+:    :+:       :+:       :+:     :+:     :+:+:   :+: \n +:+ +:+  +:+    +:+ +:+    +:+       +:+       +:+     +:+     :+:+:+  +:+ \n  +#++:   +#+    +:+ +#+    +:+       +#+  +:+  +#+     +#+     +#+ +:+ +#+ \n   +#+    +#+    +#+ +#+    +#+       +#+ +#+#+ +#+     +#+     +#+  +#+#+# \n   #+#    #+#    #+# #+#    #+#        #+#+# #+#+#      #+#     #+#   #+#+# \n   ###     ########   ########          ###   ###   ########### ###    #### \n" RESET);
        free(tab);
    }
}
