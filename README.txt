Sistemes operatius avan�ats: TheShooter
Realitzat per: Omar Ntifi Matar�n - omar.ntifi@students.salle.url.edu

1.Compilaci� del projecte:
-Entorn de Montserrat de la univeristat
-Compilar amb eina make

2.Explicaci� sistemes fitxers
-FAT16: FAT16 �s una versi� de 16 bits del sistema de fitxers FAT. Aquests tenen tots en com� que la seva estructura est� distribuida en quatre parts:
sectors reservats, la regi� fat, la regi� del directori root i la regi� de dades. Als sectors reservats trobem tota la informaci� respecte al propi sistema de fitxers (Bios i BootSector)
mentre que la regi� del directori root �s la que hem utilitzat per trobar els fitxers a partir d'aquest. A la regi� de dades tenim les dades dels fitxers.

-EXT2: EXT2 �s un altre tipus de sistema de fitxers per� que s'organitza diferent i per tant la seva gesti� tamb� ho �s. Aquest tipus de sistema contenen una taula on trobam estructures
de dades anomenades inodes que contenen informaci� d'adre�es, noms... d'altres fitxers. En cas contrari al FAT16 el nom d'aquest fitxer �s variable, �s a dir, no sabem quant ocupen, 
per aix� aquests inodes inclouen tamb� un camp per indicar la llarg�ria d'aquests noms.

3.Explicaci� de la pr�ctica
  a-Requeriments: s'ha d'aconseguir seguir les intruccions de l'usuari per gestionar uns sistemes de fitxers.
Aquests �nicament s�n gestionats si son FAT16 o EXT2. D'aquests sistemes podem treure la seva info i cercar o esborrar fitxers que es troben continguts en ells.

  b-Disseny: aquest programa ha estat desenvolupat amb forma de ceba, es a dir, cada fase fa utilitzar l'anterior. Per comen�ar es va fer la fase 1 on s'aconsegueix
tota la informaci� del sistema de fitxers. Per la fase 2, s'utilitzen les dades de l'anterior per trobar fitxers dins del sistemes. La fase 3 amplia la fas2 afegint
una capa de recursivitat per poder trobar fitxers als subdirectoris. Per �ltim la fase 4 (delete) utilitza totes les anteriors per saber informaci� i trobar (find)
els fitxers (tamb� a subdirectoris) i esborrar-los.

  c-Estructures de dades: les estructures de dades utilitzades s'han fet servir per facilitar les lectures del fitxer i gestionar de forma m�s �gil aquesta informaci�
Aquestes estructures s'han creat amb l'ajuda de les guies del estudy i cercan per internet. Les estructures s�n les seg�ents: per FAT16 tenim Bpb i Bs que representen
els parametres de la Bios i el BootSector del sistema de fitxers. Per part de EXT2 tenim m�s estructures ja que la seva organitzaci� �s m�s complexa. Tenim el ext2_super_block que representa
tota la informaci� del sistema de fitxers ext2. La estructura Inode que representa un inode del sistema de fitxers i DirectoryEntry que representa una entrada de directori.

  d-Proves realitzades: per a saber si els resultats obtinguts son bons s'ha comparat amb exemples de l'enunciat i s'ha fet �s de l'eina printf per veure que les
dades obtingudes tenien sentit. Com tractam fitxers i llegim bytes �s f�cil saber si la dada �s correcta ja que sino surten car�cters estranys.

  e-Problemes observats: El major problema que ha sorgit en aquesta pr�ctica ha sigut saber escollir el tipus de dades que es fa servir per llegir una variable. �s a dir,
si llegies m�s bytes que el tipus permitia el programa feia core dumped, i si tenies espai pero no llegies la informaci� que tocaba tenies dades incorrectes. Aix� s'ha anat
solucionant cercant informaci� dels tipus de dades a internet, fent us de les guies del estudy i sobretot fent prova i error al programa.

  f-Estimaci� temporal: FASE1 (9h) + FASE2 (12h) + FASE3 (5h) + FASE4 (6h) = 32h

4.Explicaci� Git: Mitjan�ant git per comandes i GitKraken s'han gestionat les versions de la practica.
Aquesta ha seguit un patr� de dues branches per fase corresponent cadascuna a un tipus de sistema de fitxer (FAT16 o EXT2).
Totes les branches han sigut seq�encials per evitar conflictes. A m�s per cada fase s'ha creat una branch espec�fica.
L'us de git no ha estat molt complicat ja que �s una eina basica al m�n de la inform�tica.

5.Conclusions generals.
Despr�s d'haver acabat la pr�ctica, es veu clarament que l'important a l'hora de gestionar aquest tipus de sistema de fitxers �s comprendre com estan estructurats,
ja que una vegada ho entens, el realitzar el programa dep�n m�s de les habilitats que tingui cadasc� per desenvolupar programari. De fet el entendre com funcionen aquests sistemes i
documentar-me ha estat el que m�s temps m'ha portat. Fent una comparaci� entre els dos tipus de sistema, m'ha resultat bastant m�s senzill treballar amb els FAT16 ja que �nicament es
van llegint bytes i avan�ant de bloc en bloc. D'altra banda ext2 s'estructura amb una taula i inodes, cosa que conceptualment m'ha portat m�s temps d'entendre i de treballar.
  

6.Bibliografia
https://www.nongnu.org/ext2-doc/ext2.html#idm140660447281728
http://www.science.smith.edu/~nhowe/teaching/csc262/oldlabs/ext2.html
http://classpage.dmorgan.us/cs40/analyze-ext2.htm
http://www.maverick-os.dk/FileSystemFormats/FAT16_FileSystem.html
https://www.analog.com/media/en/technical-documentation/application-notes/ee_329_rev1.pdf
https://wiki.osdev.org/Ext2#Locating_the_Superblock


