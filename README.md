# Kiriko and the Donuts (parte 2/kkk)
Si parte due perchè parte 1 era per showoff / teaser ma magari anche la parte 2 sarà simile.

## Features generali
(forza kiriko team)

### Lobby
#### Componenti presenti:
- **menù**
- **sfondo** (animato / statico)
- **music player** (offre un set di brani lobby che l'user può scegliere, vedi [MUSIC PLAYER](#music-player))
- **modalità di input** (WASD / frecette / mouse)

#### Menù:
- [Training](#training)
- [Survival](#survival)
- [Duel](#duel)
- [Settings](#settings)
- [How to play](#how-to-play)
- [Credits](#credits)
- [Exit](#exit)


### Training
#### Descrizione
Kiriko può allenarsi all'interno di un dojo per migliorare la propria mira, provare le sue abilità e sperimentare combattimenti con nemici moddati (all'eventuale sconfitta del player, kiriko verrà semplicemente rigenerata al centro della mappa)

#### Componenti presenti:
- **scenario** (con dimensione limitata (tbd))
- **[kiriko](#dinamica-di-gioco-kiriko)**
- **menù training** (comprende menù pausa)

#### Menù Training
- switch ([Nemici](#nemici), [Player](#player))
  - menù in base allo switch
- opzioni (fa avanzare il menù di Training al menù di impostazioni)
- esci

##### Nemici
- **tipologia** (vedi [ENEMY TYPE SET](#enemy-type-set))
- **generazione** (imposta i criteri di generazione dei nemici) presenta **ON/OFF** (in base se attivo o meno)
  - **evento** (scelta in base a quali criteri si verifica la generazione, vedi [ENEMY GENERATION CRITERIA](#enemy-generation-criteria)) 
    - **densità di generazione** (è possibile scegliere la quantità di nemici generati ad ogni richiesta o ad ogni intervallo di tempo)
    - (solo per criterio:"a tempo") **intervallo di generazione** (è possibile scegliere l'intervallo di tempo di pausa di generazione dei nemici in un range (tbd) + estremo massimo rende il modificatore temporale **random** (sempre rispettando il range minimo e massimo))
- **comportamento** (vedi [ENEMY BEHAVIOUR SET](#enemy-behaviour-set))
- **punti salute** (è possibile scegliere la quantità di punti salute in un range (tbd))
- **forza** (è possibile scegliere la quantità di forza (punti salute tolti per ogni attacco) in un range (tbd))
- **velocità di movimento** (è possibile scegliere la velocità di movimento in un range (tbd))
- **velocità di attacco** (è possibile scegliere la velocità di attacco in un range (tbd))
- **dimensione** (è possibile scegliere il fattore di dimensione in un range (tbd))
- **reset** (reimposta i valori di default in base alla tipologia del nemico)

#### Player
Opzioni simili ai Nemici con aggiunte:
- **abbigliamento/skin** (vedi [KIRIKO SKIN SET](#kiriko-skin-set))
- **punti salute**
- **forza**
- **velocità di movimento**
- **velocità di attacco**
- **dimensione**
- **attacco definitivo** (è possibile scegliere l'attacco definitivo in base a quelli disponibili, vedi [KIRIKO ULT SET](#kiriko-ult-set) (futuramente modificare la durata, danno,... di quest'ultimo))
- **reset**


### Survival
Kiriko scende in campo e affronta le ciambelle! Quanti punti riuscirà a fare prima di essere mangiata? (modalità endless o a livelli?)

#### Componenti presenti:
- **menù survival**
#### Menù Survival
- **numero di player** (1-2) (modifica di conseguenza la difficoltà)
- **scenario** (vedi [SCENARIO SET](#scenario-set))
- **difficoltà** (vedi [SURVIVAL DIFFICULTY](#survival-difficulty) tbd : facile/medio/difficile o a livelli)
- **equipaggiamento** (scegli l'equipaggiamento di kiriko):
  - **attacco definitivo** (scegli l'attacco definitivo di kiriko utilizzabile in partita tra un insieme a tua scelta, vedi [KIRIKO ULT SET](#kiriko-ult-set)) 
  - (tbd: altro?)

#### Dinamica di gioco
- **scenario** (scelto in precedenza ([SCENARIO SET](#scenario-set))
- **kiriko**
- **generatore di nemici** (con criteri scelti in precedenza ([SURVIVAL DIFFICULTY](#survival-difficulty))
- **contatore del punteggio**

##### Dinamica di gioco: Kiriko
- *attacco normale :* **kunai** (mira col muose e lancia un kunai contro i nemici con tasto destro del mouse)
- (tbd) *attacco speciale*
- *attacco definitivo :* (con tbd:tasto attiva l'attacco definitivo scelto in precedenza ([KIRIKO ULT SET](#kiriko-ult-set)))

#### Dinamica di gioco: Nemici
- *attacco normale :* **ciambellata (tbd:nome)** (quando kirko è alla portata dell'attacco di un nemico (varia in base alla tipologia del nemico), quest'ultimo procede periodicamente ad infliggere danni (a kiriko))
- (tbd:boss) *attacco speciale*

#### Eventi
- **sconfitta**: verrà mostrato una schermata di riepilogo del punteggio record della partita e in assoluto (record, best record) con **menù**:
  - **riprova**
  - **esci**


### Duel
Stabilisci quale Kiriko è la migliore affrontando nemici in modalità endless, l'ultima Kiriko a rimanere in partita vince! (modalità a 2 player)
- **scenario**
- **difficoltà** (vedi [DUEL DIFFICULTY](#duel-difficulty))
- **equipaggiamento**

#### Eventi
- **sconfitta di un player**:  verrà mostrato una schermata di riepilogo del punteggio record della partita dei due player e il singolo risultato (vittoria/sconfitta) con menù:
- **riprova**
- **esci**

### Settings
Un menù che offre la possibilità di modificare un insieme di impostazioni tra cui:
- **Voulme**
  - **volume generale** (comprende musica, effetti)
  - **musica** ON/OFF
  - **volume della musica**
  - **effetti** ON/OFF
  - **volume degli effetti**
  - **reset dell'audio** 
- **Risoluzione dello schermo**
  - **modalità finestra** (Schermo intero, a finestra (richiede gestione resize), tdb:senza bordi(richiede gestione resize)) 
  - **qualità grafica**: **N.B.:** se si usa la tecnica del batch + adattamento in base allo schermo:
    - scarsa: 960x540p (PAL wd)
    - bassa: 1280x720p (HD)
    - media: 1920x1080p (FHD)
    - alta: 3840x2160p (4K UHD)
    - brlla: 15360x8640p (16K UHD)
  - **applica modifiche risoluzione**
  - **reset impostazioni della risoluzione**
- **reset generale**
- **esci** 

### How to play
Riepiloga in breve come giocare a Survival e Duel nonchè i comandi da tastiera e mouse necessari allo svolgimento del gioco e lo scopo del gioco
(schermata navigabile su/giù, esc per uscire)

### Credits
Mostra la schermata dei crediti, premere ESC per tornare alla lobby

### Exit
uscita dal gioco (tbd: scorciatoia da tastiera per uscire (se possibile quella nativa del OS))



### Music player
Si presentacome un rettangolo in basso a destra, mostra: **nome canzone** - **nome/i artista/i** sotto i tasti (**⏮ ⏯ ⏭ ⇄**) tbd:a destra dei simboli icona del brano. premere H per nascondere il riquadro.
#### Lobby
sempre presente
#### Training
presente quando si entra nel menù di Training
#### Survival/Duel
presente quando si entra nel menù di pausa


### Variabili
#### ENEMY TYPE SET
- donut
- donut king
- vero chad

#### ENEMY GENERATION CRITERIA
- a richiesta
- a tempo (comprende a tempo random)

#### ENEMY BEHAVIOUR SET
- immobile pacifico (pacific_idle)
- immobile ostile (hostile_idle)
- pacifico (pacific_follow)
- ostile (hostile_follow)

#### KIRIKO SKIN SET
- Kiriko rossa
- Kiriko blu

#### SCENARIO SET
- rurale
- città

#### SURVIVAL DIFFICULTY
tbd: a livelli o a difficoltà
##### A livelli
da pensarci...
##### A difficolta
in ordine cresecnte di difficoltà: 
- facile
- medio
- difficile
- RP
- SHION CP

#### DUEL DIFFICULTY
in ordine cresecnte di difficoltà: 
- facile
- medio
- difficile
- RP
- SHION CP

#### KIRIKO ULT SET
attivabili in Training, Survival, Duel. Ogni ULT ha una sua cinematica

- **scatto Kitsune**: aumenta velocità di attacco e velocità di movimento, riduce tempo di abilità speciale (se esiste) per 5.67 secondi
- **portafortua Suzu**: rende immune a qualsiasi attacco per 1 secondo, aumenta istantaneamente la vita di una certa quantità
- **attacco della Kitsune**: provoca una certa quantità di danno istantaneamente a tutti i nemici in un certo raggio di azione 
- **Ofuda**: rigenera una certa quantità di salute entro un certo tempo (e rende immuni ad ogni eventuale debuff)

