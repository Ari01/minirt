#include "01_09_02_bmp.h"

int main()
{
	int i,j;
	Image* I = NouvelleImage(256,256);
	for(i=0;i<256;i++)
	{
		for(j=0;j<256;j++)
		{
			Pixel p;
			p.r = i;
			p.g = j;
			p.b = 0;
			SetPixel(I,i,j,p);
		}
	}
	//Image* I = Charger("test.bmp");
	Sauver(I,"test.bmp");
	DelImage(I);
	return 0;
}


/*!F
	Ah ! Le format BMP est intéressant. 
	Voila un bon exercice pour débuter dans l'écriture/lecture de fichiers binaires.

	Ce format est relativement facile, mais va quand même faire peur aux novices du domaine.

	Alors regardons le main, ainsi que le .h : ce sont les mêmes que l'exemple précédent sur les PPM.
	Je vous laisse regarder l'exemple précédent.

	De même toutes les fonctions, sauf chager et sauver sont les mêmes.

	Je ne parlerai donc ici que des fonctions charger et sauver.

Tout d'abord, une description du format BMP.
Une documentation ici :

http://www.commentcamarche.net/contents/video/format-bmp.php3

	Un BMP, c'est un header (des données), et ensuite le pixels les uns à la suite des autres, non compressés.

	Voyons le header.

	Le Header se compose de plusieurs choses : 
    - la signature BM : il existe d'autres signatures, mais on ne considerera que celle la, regardez le premier
      test de sortie de la fonction charger.
    - la taille du fichier
    - 4 octets à 0
    - l'offset de l'image : ou est ce que les données commencent.

	Dans notre cas, ce sera toujours à 54, après la taille du header.

	Vous voyez que j'ai fait des structures qui correspondent à cela dans bmp.c

	Le #pragma pack(1) permet de désactiver l'alignement mémoire : cherchez sur ce recueil ce qu'est l'alignement mémoire
	Vous comprendrez qu'il faut la désactiver, car sur le disque, il n'y a pas de "trous" entre les données.
	Il faut donc que notre structure soit contigue en mémoire, car on va l'écrire d'un seul coup.

	Nous avons ensuite une sous structure Entête de l'image (bien expliquée dans le lien ci dessus). Nous avons :
    - sa taille (40)
    - la largeur et la hauteur de l'image (important !) regardez dans charger et sauver, je les associe à I->w et I->h
    - le nombre de plans (toujours à 1 : des extentions du format BMP qui n'ont jamais été exploitées)
      j'imagine qu'il était prévu de faire des fichiers BMP a plusieurs plans, plusieurs images dans le même fichier ? 
      des layers ? ça n'a jamais été exploité.
    - Méthode de compression : pareil, rares sont les BMP compressés. On preferera d'autres formats pour compresser.
      Donc on ne lira, et écrira que des BMP non compressés.
    - résolution horizontale ou verticale. ça c'est utile pour imprimer par exemple. Si vous avez une image, et que vous 
      voulez l'imprimer, quelle taille fera-t-elle sur le papier ? En fonction de son nombre de pixels ? On peut renseigner
      ça ou pas. Moi je mets des 0 (et je lis des 0 sur les BMP que j'ai créé avec Paint), en gros, on s'en fout : le gars
      qui veut imprimer l'image se débrouillera pour lui donner la taille qu'il veu manuellement.
    - la palette (et les couleurs importantes de la palette)

Alors la palette, dans notre cas, on s'en fout : il n'y en a pas. 
En effet, en 24 bpp (ce que je supporte uniquement), chaque pixel embarque ses couleurs.

Dans les formats plus pauvres (256 couleurs), chaque pixel est codé sous un seul octet. Cet octet, ce n'est pas une couleur, mais
un index vers une palette existante. On définit 256 couleurs dans une palette, juste en dessous du header,et chaque pixel,
avec un seul octet (entre 0 et 255) est un index vers une couleur de la palette.
L'image est bien plus compacte, mais n'a que 256 couleurs maximum. Et si vous changez une couleur, tous les pixels utilisant
la même couleur seront donc changés en conséquence !

Ici donc, pas de palette : chaque pixel est indépendant et coute 3 octet (24 bits).

Voila pour le header.
On lit et on écrit le header d'un seul coup avec un fread ou un fwrite bien placé.

Passons maintenant à l'image elle même !

Les pixels sont codés les uns à la suite des autres.
On pourrait donc se dire "un grand fread et c'est plié !"

Cependant, hélas, nous ne stockons pas, ma structure et les BMP, les choses de la même façon.

Ma structure est ainsi faite :
1) Je code les pixels de gauche à droite, puis de haut en bas (sens de lecture occidental)
2) mes pixels sont tous de 3 octets, codés en rouge, vert, bleu (RGB) dans cet ordre.
3) tout se suit en mémoire (mon tableau dat n'a pas de trous)

Donc c'est simple !

Mais le format BMP est différent :
1) stockage des pixels de gauche à droite, mais de ---> BAS EN HAUT <---

Donc vous remarquerez dans ma fonction charger et sauver, les pixels sont lus/écrits non pas à position i,j
par rapport à ma structure, mais i,I->h-j-1, ce qui permet de bien mettre les pixels ou il faut.

2) stockage en bleu, vert, rouge (BRG), je suis donc obligé de passer par un triplet d'octets temporaire (bgrpix)
que je croise pour le remplissage avec ma structure Pixel (le r devient le bgrmix[2] et non [0])

3) et non des moindres, il existe ce qu'on appelle le picth.
Le pitch, c'est le nombre d'octets que prend une ligne, et le format BMP IMPOSE qu'une ligne soit multiple de 4 octets.
Cela permet, dans certains anciens buffer graphiques, de charger le BMP d'un seul coup, pour un blit rapide :
on perd quelques octets, mais on gagne énormément en ne gérant pas de cas particulier en arrivant en bout de ligne avec
un pross 32 bits, bref.

Donc chaque pixel fait 3 octets, j'ai X pixels par ligne. et 3*X n'est pas nécessairement un multiple de 4.
Le reste de la division de 3*X par 4 me dit combien d'octets sont en plus. Et en conséquence, je complète par des 0
J'appelle pitch le nombre d'octets à rajouter ici.

Si (3*X)%4 == 0, je ne rajoute rien : pitch = 0
Si (3*X)%4 == 1, je dois rajouter 3 octets (pour compléter)
Si (3*X)%4 == 2, je dois rajouter 2 octets (pour compléter)
Si (3*X)%4 == 3, je dois rajouter 1 octets (pour compléter)

Mon tableau corrpitch permet de considérer rapidement chacun de ces 4 cas en évitant 4 if.

Voila, il ne me reste plus qu'à écrire ou lire l'image...

Ensuite, je manipule de la même manière que dans l'exemple précédent.

Et c'est du BMP officiel, vous pouvez l'ouvrir avec Paint ou autre !

!*/

/*!E
	No explanations yet.
!*/

/*
titre: Lire et écrire des fichiers image BMP
titreE: Read and Write a BMP file.
meta: C;BMP natif
metaE: C;native BMP 
desc: Lire et écrire nativement des fichiers image BMP
descE: Read and Write a BMP file from scratch
cle  : 
linkT: 01_09_02_bmp.h
linkT: 01_09_02_bmp.c
*/

