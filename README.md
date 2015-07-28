## Mutliwii 2.3 + GPS NAV 
### Drotek Drofly V3 support
### Code version 1.4 (final version)
### Code based on Multiwii 2.3 + Nav b7 (eosbandi)
===============================

_**features added by Wareck (wareck@gmail.com):**_

- DroflyV2 and DroflyV3 boards integration
- code integration for SDCARD and corrective patch for datalogger
- corrective patch for variometer error
- corrective patch for failsafe bug
- integrate code volume fly restriction "Wadudu"
- Add PCF8591 I2C ADC card support
- add build error if SDCARD options aren't well tuned in config.h
- Sbus Corrective patch (can use orangeRX or futaba sbus, need an inverter http://www.fernitronix.fr/fr/multi-copters/les-gadgets-multiwii/les-recepteurs-sbus-et-multiwii-2-3 )
- Corrective patch for Barometer
- Allow code works without GPS
- Allow 6 position switch for AUX
- French conversion for some compilation error code
-Add restriction volume Fly RTH function (thanks to the wadudu Team !)

_**Améliorations apportées par Wareck (wareck@gmail.com):**_
- intégration des cartes DroflyV2 et DroflyV3
- Intégration du support SDCARD et correction de quelques bugs du datalogger
- Correction d'un bug du variomètre
- Correction d'un bug lié au failsafe
- Ajout du code de restriction de vol "Wadudu"
- Ajout du support des cartes PCF8591 I2C ADC
- Ajout d'une boucle de contrôle sur la validité des options SDCARD dans config.h
- Patch correctif pour le SBUS (permet l'utilisation de récepteur orangeRX/futaba SBUS, inverseur nécessaire http://www.fernitronix.fr/fr/multi-copters/les-gadgets-multiwii/les-recepteurs-sbus-et-multiwii-2-3 )
- Correction des calculs pour le baromètre
- Ajout d'option permettant au code de fonctionner sans GPS
- Utilisation possible d'inter 6 positions pour les voies AUX
- Traduction en français des messages d'alerte lors de la compilation
- Ajout de la fonction RTH en cas de depassement de la zone de vol (merci la team ! )
