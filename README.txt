Sistemes operatius avançats: TheShooter
Realitzat per: Omar Ntifi Matarín - omar.ntifi@students.salle.url.edu

1.Compilació del projecte:
-Entorn de Montserrat de la univeristat
-Compilar amb eina make

2.Explicació sistemes fitxers
-FAT16: FAT16 és una versió de 16 bits del sistema de fitxers FAT. Aquests tenen tots en comú que la seva estructura està distribuida en quatre parts:
sectors reservats, la regió fat, la regió del directori root i la regió de dades. Als sectors reservats trobem tota la informació respecte al propi sistema de fitxers (Bios i BootSector)
mentre que la regió del directori root és la que hem utilitzat per trobar els fitxers a partir d'aquest. A la regió de dades tenim les dades dels fitxers.

-EXT2: EXT2 és un altre tipus de sistema de fitxers però que s'organitza diferent i per tant la seva gestió també ho és. Aquest tipus de sistema contenen una taula on trobam estructures
de dades anomenades inodes que contenen informació d'adreçes, noms... d'altres fitxers. En cas contrari al FAT16 el nom d'aquest fitxer és variable, és a dir, no sabem quant ocupen, 
per això aquests inodes inclouen també un camp per indicar la llargària d'aquests noms.

3.Explicació de la práctica
  a-Requeriments: s'ha d'aconseguir seguir les intruccions de l'usuari per gestionar uns sistemes de fitxers.
Aquests únicament són gestionats si son FAT16 o EXT2. D'aquests sistemes podem treure la seva info i cercar o esborrar fitxers que es troben continguts en ells.

  b-Disseny: aquest programa ha estat desenvolupat amb forma de ceba, es a dir, cada fase fa utilitzar l'anterior. Per començar es va fer la fase 1 on s'aconsegueix
tota la informació del sistema de fitxers. Per la fase 2, s'utilitzen les dades de l'anterior per trobar fitxers dins del sistemes. La fase 3 amplia la fas2 afegint
una capa de recursivitat per poder trobar fitxers als subdirectoris. Per últim la fase 4 (delete) utilitza totes les anteriors per saber informació i trobar (find)
els fitxers (també a subdirectoris) i esborrar-los.

  c-Estructures de dades: les estructures de dades utilitzades s'han fet servir per facilitar les lectures del fitxer i gestionar de forma més àgil aquesta informació
Aquestes estructures s'han creat amb l'ajuda de les guies del estudy i cercan per internet. Les estructures són les següents: per FAT16 tenim Bpb i Bs que representen
els parametres de la Bios i el BootSector del sistema de fitxers. Per part de EXT2 tenim més estructures ja que la seva organització és més complexa. Tenim el ext2_super_block que representa
tota la informació del sistema de fitxers ext2. La estructura Inode que representa un inode del sistema de fitxers i DirectoryEntry que representa una entrada de directori.

  d-Proves realitzades: per a saber si els resultats obtinguts son bons s'ha comparat amb exemples de l'enunciat i s'ha fet ús de l'eina printf per veure que les
dades obtingudes tenien sentit. Com tractam fitxers i llegim bytes és fàcil saber si la dada és correcta ja que sino surten caràcters estranys.

  e-Problemes observats: El major problema que ha sorgit en aquesta pràctica ha sigut saber escollir el tipus de dades que es fa servir per llegir una variable. És a dir,
si llegies més bytes que el tipus permitia el programa feia core dumped, i si tenies espai pero no llegies la informació que tocaba tenies dades incorrectes. Això s'ha anat
solucionant cercant informació dels tipus de dades a internet, fent us de les guies del estudy i sobretot fent prova i error al programa.

  f-Estimació temporal: FASE1 (9h) + FASE2 (12h) + FASE3 (5h) + FASE4 (6h) = 32h

4.Explicació Git: Mitjançant git per comandes i GitKraken s'han gestionat les versions de la practica.
Aquesta ha seguit un patró de dues branches per fase corresponent cadascuna a un tipus de sistema de fitxer (FAT16 o EXT2).
Totes les branches han sigut seqüencials per evitar conflictes. A més per cada fase s'ha creat una branch específica.
L'us de git no ha estat molt complicat ja que és una eina basica al món de la informàtica.

5.Conclusions generals.
Després d'haver acabat la pràctica, es veu clarament que l'important a l'hora de gestionar aquest tipus de sistema de fitxers és comprendre com estan estructurats,
ja que una vegada ho entens, el realitzar el programa depèn més de les habilitats que tingui cadascú per desenvolupar programari. De fet el entendre com funcionen aquests sistemes i
documentar-me ha estat el que més temps m'ha portat. Fent una comparació entre els dos tipus de sistema, m'ha resultat bastant més senzill treballar amb els FAT16 ja que únicament es
van llegint bytes i avançant de bloc en bloc. D'altra banda ext2 s'estructura amb una taula i inodes, cosa que conceptualment m'ha portat més temps d'entendre i de treballar.
  

6.Bibliografia
https://www.nongnu.org/ext2-doc/ext2.html#idm140660447281728
http://www.science.smith.edu/~nhowe/teaching/csc262/oldlabs/ext2.html
http://classpage.dmorgan.us/cs40/analyze-ext2.htm
http://www.maverick-os.dk/FileSystemFormats/FAT16_FileSystem.html
https://www.analog.com/media/en/technical-documentation/application-notes/ee_329_rev1.pdf
https://wiki.osdev.org/Ext2#Locating_the_Superblock


