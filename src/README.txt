DOSSIER IMPORTANT:
	- Custom_Devices : contient tous les modules créés pour implémenter notre fonction

FICHIERS IMPORTANTS:

	- src/Makefile	
	- src/Donnees_Spotify.txt : simule la base de données de musique de Spotify
	- src/Internet_Spotify.txt : simule la liste des couples user/password que Spotify connait
	- src/Bluetooth_Device.txt : simule la liste des appareils bluetooth dans les environs
	- src/on.txt : simule un bouton on/off

FONCTIONNEMENT:
	
	1) Dans le fichier core_simulation se trouve 3 constantes:
		string const url; => Doit être rempli avec l'url du site ex: "www.spotify.com"
		string const user; => Le user du compte Spotify ex: "Juliette"
		string const password; => Le user du compte Spotify ex: "mdp2"
			/!\ ATTENTION /!\ Le couple user/password doit exister dans le fichier 
			src/Internet_Spotify.txt sinon le programme ne pourra jamais continuer et 				précisera s'il s'agit d'un erreur de user ou de password
	
	2) Ces 3 données sont envoyés au module Wifi par le bus I2C et traité
	
3) Le module Wifi simule la connexion au compte Spotify

4) Le module Bluetooth se connecte et rencence tous les appareils dans les environs

5) L'utilisateur doit faire un choix end tapant directement sa réponse sur le terminal: la réponse est le chiffre qui correspond à l'appareil auquel on veut se connecter

6) Le pulse sensor mesure une pulsation et renvoit la valeur de celle-ci: Nous avons simulé une entrée analogique malgré que le vrai capteur envoit une PWM car simuler un système de gestion d'interruption sur front montant pour calculer la période nous aurait pris trop de temps. De ce fait, on a supposé que le capteur faisait lui-même le calcul de la pulsation et envoyait cette donnée analogique sur le pin d'entrée.

7) On soumet une requête de musique dont les BPM sont égaux à ceux de la pulsation de l'utilisateur

8) Notre processeur contient une liste de musique en mémoire et sélectionne donc celle que Spotify lui a désigné

9) Les données sont envoyé au module blutetooth par le nouveau bus UART pour jouer la musique
