# 2021_2022_Saillard_Grau

# Gas sensor connected Project

## SUMMARY

* 1 [Project description](#description)
* 2 [Gas sensor based on nanoparticles](#paragraph2)
* 3 [Analog circuit + PCB Elaboration](#paragraph3)
* 4 [Microcontroler and Open Source Hardware](#paragraph4)

-------

## 1 - Project description <a name="description"></a>

This projet is realised in the UF "SmartDevice" of the MSIoT master.
The aim is to design and build a smart device based on the combination of a gas sensor and an electronic card to communicate data over a low speed network.
This project addresses many concepts: the physics of nanoparticle sensors, the writing of a datasheet, analog electronics, Arduino Uno, the production of a PCB, the design of a test bench and communication via wireless network.

*Deliverables* :

1. Gas sensor Datasheet : Composed of a description, specifications, specifics characteristics (electrical, thermal), package dimensions and typical applications in a datasheet document.
2. Analog circuit + PCB Elaboration : The board accepts two gas sensors inputs with a transimpedence conditionner. It can be plug on an Arduino Uno Board below and a LoRa module board can be plug on the top.
3. Microcontroler and Open Source Hardware: ARDUINO code has in input one of the 2 annalog gas sensor voltage and a digit input for the choice of sensor. It transmits gas concentration variation to The Thing Networks via a LoRa RN2483 component.

-------

## 2 - Gas sensor based on nanoparticles <a name="paragraph2"></a>

The gas sensor was made by ourself in the AIME (Atelier Interuniversitaire de Miro-nano Electronique) clean room with chemicals technics.
The process breaks down into 4 major steps:

### WO3 nanoparticles (NPs) synthesis

This synthesis follows a protocol which can be found in a scientific article called "An Inorganic Route for Controlled Synthesis of W18O49 Nanorods and Nanofibers in Solution".
This is divided in two steps:

* WO3 seeds preparation
* WO3 nanowires growth

### Building of the microelectronic devices

The dies of chips ares composed of 4 elements who were manufactured by different phasesof doping and photolithography:

* A buried heater (n-doped polysilicon).
* An Aluminium (Al) resistance which can be used as a heater or a thermistor, located at the surface of the chips.
* 2 interdigitated electrodes xhich will host the layer of nanoparticles and which will then become sensitive to the gaseous environment.
You can see below the process:

![image](Images/dies_composition.png)

### Integration of the active layer of NPs

The dies was placed on a TO5-10 box.
A small amount of aqueous NPs solution is deposited directly on the chip. The interdigitated comb is then polarized with a sinosoidal voltage of frequency 100kHz and amplitude 10V. This voltage is left for the duration of the integration.
After a cleannig phase , the integrated sensor can be observed under an optical microscope.

![image](Images/integrated_sensor.png)

### Electrical characterization of the sensor under controlled atmosphere

Then the gas sensor is ready for evaluation. We check the variation of its restistance in the presence of aspecific gas at given concentration.
The two gases used was anmmonia (NH3) and ethanol (C2H6O), at a concentration of 0.1% in dry air (80%N2 - 20%O2).
All essential electricals characteristics were measured and a datasheet was built there : >AIME [datasheet]

-------

## 3 - Analog circuit + PCB Elaboration <a name="paragraph3"></a>

### Analog Circuit Simulation

The goal of this part was to simulate our sensor and its associated electronic diagram thanks to LTSpice.
The sensor resistivity is up the Giga Ohms so to measure it we have to inject a voltage reference and by a bridge resistor and an amplifier to amplifier the signal to acquire it.
The LT1050 choice is done because of is a high performance and zero-drift amplifier. It is often use to measure low signal sensors.

### Conditioner Diagram

![image](Images/Conditioner_Diagram.png)

In order to obtain the cutoff frequencies of the different steps and observe the noise attenuations at 50kHz and at the Nyquist frequency.
To remember, the cutoff frequency is calculate by this formula: fc = 1 / (2 *𝜋* R * C)

The first passive bypass filter is composed of C1 and R1 components, the aim is to attenuate the 230VAC-50Hz frequency with fc = 15.9Hz.
The second one composed by C4 and R3 is an active bypass with a cutoff frequency fc = 1.6Hz
The third one composed by R6 and C2 is a passive bypass with fc = 1.6kHz to cutoff the noise make by the processing.
The  Analog to Digital Converter of the microcontrolerhas a sample frequency of 200Hz for 13bits so a frequnec by bit of 15kHz. If we take the middle of this the frequency, we have d Nyquist frenquency of 7.75kHz. It is why we choose the fc = 1.6Khz to be sure of the well done cutoff.

### Filters characteristics

![image](Images/Condtionner_Filters_Characteristics.png)

After this simulation phase, we are able to design an electronic architecture.

### Electronic Diagram

![image](Images/Electronic_Diagram.png)

### TODO Kicad

* [x] Create Kicad project
* [x] Design the circuit board
* [x] Assign the components footprints
* [x] Design of the pcb
* [x] Component placement
* [x] Routing

### Schematic

![image](Images/schematic.png)

### Placement and Routing

We made it clear not to build a ground plane on the circuit.
Indeed there could have been short-circuits with the tracks because of the INSA manufacturing method.
The jumpers JP1, JP2 and JP3 are only straps to keep one bottom side soldering.
We can choose which sensor to use (the SEED grove MCQ5 or the GSWO3AIME) by strapping J5 and J4 pins by a jumper.
The LoRa RNB2483/2993 module given by INSA and sell at Drazzy.com will be plug on the topside of the board on J3.

![image](Images/TopLayer.png)

![image](Images/BottomLayer.png)

### 3D View

You can see:
* S1 location where the nano sensor could be solder or put on a specific TO5 socket
* J1 for the external heater power supply
* J2 for a Industrial SEED Grove sensor
* J4 and J5 for the sensor choice

![image](Images/TopView.png)

![image](Images/BottomView.png)

## 4 - Microcontroler and Open Source Hardware <a name="paragraph4"></a>

This part was focused on exploiting the data from the gas sensor. The idea is to recover the data from the sensor using an Arduino electronic board and process this data with the Arduino software then send it over the LoRa network and retrieve it on The Things Network.

You'll find the related files under >LoRa_gaz_sensor>LoRa_gaz_sensor.ino

## Contribution

### Students

* Victor GRAU
* François SAILLARD

### Tutors

* Jérémie GRISOLIA
* Arnauld BIGANZOLI
* Benjamin MESTREAIME

