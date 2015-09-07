
/*
 * Welcome to MultiWii.
 *
 * If you see this message, chances are you are using the Arduino IDE. That is ok.
 * To get the MultiWii program configured for your copter, you must switch to the tab named 'config.h'.
 * Maybe that tab is not visible in the list at the top, then you must use the drop down list at the right
 * to access that tab. In that tab you must enable your baord or sensors and optionally various features.
 * For more info go to http://www.multiwii.com/wiki/index.php?title=Main_Page
 *
 * Have fun, and do not forget MultiWii is made possible and brought to you under the GPL License.
 *
 * Version 1.5, Code based on Multiwii 2.4 and Nav b7 from eosbandi
 */

/*=================================================================================
 Don't forget to copy "SDfat" folder intor your arduino/libraries directory !
 N'oubliez pas de copier le dossier "Sdfat" dans votre dossier arduino/librairies! 
 ==================================================================================*/ 

#ifdef MWI_SDCARD
#include <SdFat.h>
#endif

/*
----------------------------------------------------------------
Modification done by Olivier FERNANDEZ wareck@gmail.com:
----------------------------------------------------------------
-code merged to Multiwii v2.4
-DroflyV2 and DroflyV3 boards integration
-code integration for SDCARD and corrective patch for datalogger
-corrective patch for variometer error
-corrective patch for failsafe bug
-integrate code volume fly restriction "Wadudu"
-Add PCF8591 I2C ADC card support
-add build error if SDCARD options aren't well tuned in config.h
-Sbus Corrective patch (can use orangeRX or futaba sbus, need an inverter http://www.fernitronix.fr/fr/multi-copters/les-gadgets-multiwii/les-recepteurs-sbus-et-multiwii-2-3 )
-Corrective patch for Barometer
-Allow code works without GPS
-Allow 6 position switch for AUX
-French conversion for some compilation error code
-Add restriction volume Fly RTH function (thanks to the wadudu Team !)
-Add Generic pulse Sonar support (SR04)
-Autoland on battery fail feature


----------------------------------------------------------------
Modification apportées par Olivier FERNANDEZ wareck@gmail.com
----------------------------------------------------------------
-portage du code sur la version Multiwii v2.4
-intégration des cartes DroflyV2 et DroflyV3
-Intégration du support SDCARD et correction de quelques bugs liés au datalogger
-Correction d'un bug du variometre
-Correction d'un bug lié au failsafe
-Ajout du code de restriction de vol "Wadudu"
-Ajout du support des cartes PCF8591 I2C ADC
-Ajout d'une boucle de controle sur la validité des options SDCARD dans config.h
-Patch correctif pour le SBUS (permet l'utilisation de recepteur orangeRX/futaba SBUS, inverseur necessaire http://www.fernitronix.fr/fr/multi-copters/les-gadgets-multiwii/les-recepteurs-sbus-et-multiwii-2-3 )
-Correction des calculs pour le baromètre
-Ajout d'option permettant au code de fonctionner sans GPS
-Utilisation possible d'inter 6 poisitions pour les voies AUX
-Traduction en français des messages d'aletre lors de la compilation
-Ajout de la fonction RTH en cas de depassement de la zone de vol (merci la team wadudu! )
-Ajout du support des Sonar Generic (SR04)
-Fonction Autoland en cas de batterie vide
*/
					 

