DOSSIER IMPORTANT:
	- Custom_Devices : contient tous les modules créés pour implémenter notre fonction
	- src : contient les éléments de base du projet et un board manager pour implémenter les fonctions intermédiaires nécessaires pour réaliser la fonction voulue

FICHIERS IMPORTANTS:

	- src/Makefile	
	- src/Donnees_Spotify.txt : simule la base de données de musique de Spotify (bpm/nom/notes)
	- src/Internet_Spotify.txt : simule la liste des couples user/password que Spotify connait
	- src/Bluetooth_Device.txt : simule la liste des appareils bluetooth dans les environs
	- src/on.txt : simule un bouton on (nous n'avons pas implémenté la fonction off)

FONCTIONNEMENT:
	
	1) Dans le fichier core_simulation se trouve 3 constantes:
		string const url; => Doit être rempli avec l'url du site ex: "www.spotify.com"
		string const user; => Le user du compte Spotify ex: "Juliette"
		string const password; => Le user du compte Spotify ex: "mdp2"
			/!\ ATTENTION /!\ Le couple user/password doit exister dans le fichier src/Internet_Spotify.txt sinon le programme ne pourra jamais continuer et précisera s'il s'agit d'un erreur de user ou de password
	
	2) Ces 3 données sont envoyés au module Wifi par le bus I2C et traitées
	
	3) Le module Wifi simule la connexion au compte Spotify
			/!\ ATTENTION /!\ Si le user ou le password sont faux une exception est levée et le programme s'arrête

	4) Le module Bluetooth se connecte et rencence tous les appareils dans les environs

	5) L'utilisateur doit faire un choix end tapant directement sa réponse sur le terminal: la réponse est le chiffre qui correspond à l'appareil auquel on veut se connecter
			/!\ ATTENTION /!\ Si le choix de l'utilisateur n'est pas dans la liste, une exception est levée et le programme s'arrête
		NB: Nous avons choisi de taper directement la réponse sur le terminal même si cela ne représente pas réellement un interaction avec du hardware car nous aurions dû implementer une classe Clavier héritant de Device qui aurait lu la réponse que l'on aurait écrite directement dans un fichier texte ou depuis le terminal. Cela n'avait pas de grand intérêt étant donné ce qui a déjà été fait avant

	6) Le pulse sensor mesure une pulsation et renvoie la valeur de celle-ci. La board lit 10 valeurs pour faire une moyenne et arrondit à la dizaine près.
		NB:Nous avons simulé une entrée analogique malgré que le vrai capteur envoie une PWM car simuler un système de gestion d'interruption sur front montant pour calculer la période nous aurait pris trop de temps. De ce fait, on a supposé que le capteur faisait lui-même le calcul de la pulsation et envoyait cette donnée analogique sur le pin d'entrée.

	7) On soumet au module wifi une requête de musique dont les BPM sont égaux à ceux de la pulsation de l'utilisateur
			/!\ ATTENTION /!\ Une musique avec les BPM souhaités doit exister dans le fichier src/Donnees_Spotify.txt sinon le Board-loop ne se débloque jamais. La musique doit respecter la synthaxe suivante: "bpm:nom:<10 int pour les notes séparées d'une virgule (sauf la dernière) et sans espace>

	8) On récupère la musique et on stocke la stocke dans notre bibliothèque si elle n'existe pas déjà

	9) Les données de la bibliothèque sont envoyées au module bluetooth sur le nouveau bus UART pour jouer la musique sur l'appareil bluetooth de type casque
