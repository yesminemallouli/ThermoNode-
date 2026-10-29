# Journal des défauts — TP3 ThermoNode

| ID | Composant | Défaut recherché | Test de détection | Statut |
|---|---|---|---|---|
| DEF-01 | Conversion température | Vérification incorrecte de la limite supérieure | test_EF05_range_check_bounds | À confirmer |
| DEF-02 | Filtre | Dépassement de tampon | test_filter avec AddressSanitizer | À confirmer |
| DEF-03 | Seuil d'alarme | Compteur non réinitialisé sous le seuil | test_EF04_counter_resets_below_threshold | À confirmer |
| DEF-04 | Trame | Défaut de calcul ou de validation du CRC | test_frame | À confirmer |
| DEF-05 | Tampon circulaire | Mauvaise gestion de la capacité du tampon | test_ringbuf | À confirmer |
| DEF-06 | Machine à états | Récupération incorrecte après l'état DÉFAUT | test_node | À confirmer |
| DEF-07 | Passerelle | Défaut de traitement des trames | tests unitaires Python | À confirmer |
| DEF-08 | Passerelle | Défaut de gestion d'un message ou d'un état | tests unitaires Python | À confirmer |
