EESchema Schematic File Version 4
LIBS:outer_ball_board-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Outer Navball"
Date "2019-03-21"
Rev "v01"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Auth: Francois Gaudin"
$EndDescr
$Comp
L navball:SN74HC165 U?
U 1 1 5C951B96
P 5500 3800
F 0 "U?" H 5475 4665 50  0000 C CNN
F 1 "SN74HC165" H 5475 4574 50  0000 C CNN
F 2 "" H 5500 4550 50  0001 C CNN
F 3 "" H 5500 4550 50  0001 C CNN
	1    5500 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C952768
P 6000 4250
F 0 "#PWR?" H 6000 4000 50  0001 C CNN
F 1 "GND" H 6005 4077 50  0000 C CNN
F 2 "" H 6000 4250 50  0001 C CNN
F 3 "" H 6000 4250 50  0001 C CNN
	1    6000 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5C952E10
P 6000 4050
F 0 "#PWR?" H 6000 3900 50  0001 C CNN
F 1 "+5V" H 6015 4223 50  0000 C CNN
F 2 "" H 6000 4050 50  0001 C CNN
F 3 "" H 6000 4050 50  0001 C CNN
	1    6000 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 4050 6000 4050
Wire Wire Line
	5900 4200 6000 4200
Wire Wire Line
	6000 4200 6000 4250
$Comp
L power:GND #PWR?
U 1 1 5C953C48
P 6350 3350
F 0 "#PWR?" H 6350 3100 50  0001 C CNN
F 1 "GND" H 6355 3177 50  0000 C CNN
F 2 "" H 6350 3350 50  0001 C CNN
F 3 "" H 6350 3350 50  0001 C CNN
	1    6350 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 3350 6350 3350
Text GLabel 5900 3200 2    50   Input ~ 0
clock
Text GLabel 5900 3500 2    50   Input ~ 0
load
Text GLabel 5050 3700 0    50   Input ~ 0
motor1_2
Text GLabel 5050 3800 0    50   Input ~ 0
motor1_3
Text GLabel 5050 3600 0    50   Input ~ 0
motor1_1
Text GLabel 5050 3900 0    50   Input ~ 0
motor1_4
Text GLabel 5050 4000 0    50   Input ~ 0
motor2_1
Text GLabel 5050 4100 0    50   Input ~ 0
motor2_2
Text GLabel 5050 4200 0    50   Input ~ 0
motor2_3
Text GLabel 5050 4300 0    50   Input ~ 0
motor2_4
$Comp
L Connector:Conn_01x03_Male J?
U 1 1 5C9554B2
P 7950 3850
F 0 "J?" H 8058 4131 50  0000 C CNN
F 1 "L5G" H 8058 4040 50  0000 C CNN
F 2 "" H 7950 3850 50  0001 C CNN
F 3 "~" H 7950 3850 50  0001 C CNN
	1    7950 3850
	1    0    0    -1  
$EndComp
Text GLabel 8150 3750 2    50   Input ~ 0
latch
$Comp
L power:+5V #PWR?
U 1 1 5C9568F8
P 8500 3900
F 0 "#PWR?" H 8500 3750 50  0001 C CNN
F 1 "+5V" H 8515 4073 50  0000 C CNN
F 2 "" H 8500 3900 50  0001 C CNN
F 3 "" H 8500 3900 50  0001 C CNN
	1    8500 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C957603
P 8250 4000
F 0 "#PWR?" H 8250 3750 50  0001 C CNN
F 1 "GND" H 8255 3827 50  0000 C CNN
F 2 "" H 8250 4000 50  0001 C CNN
F 3 "" H 8250 4000 50  0001 C CNN
	1    8250 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 3950 8250 3950
Wire Wire Line
	8250 3950 8250 4000
Wire Wire Line
	8150 3850 8350 3850
Wire Wire Line
	8350 3850 8350 3900
Wire Wire Line
	8350 3900 8500 3900
$Comp
L Connector:Conn_01x03_Male J?
U 1 1 5C958436
P 7250 3850
F 0 "J?" H 7358 4131 50  0000 C CNN
F 1 "ICO" H 7358 4040 50  0000 C CNN
F 2 "" H 7250 3850 50  0001 C CNN
F 3 "~" H 7250 3850 50  0001 C CNN
	1    7250 3850
	-1   0    0    1   
$EndComp
Text GLabel 7050 3850 0    50   Input ~ 0
clock
Text GLabel 7050 3750 0    50   Output ~ 0
serial_out
Text Label 7250 3750 0    50   ~ 0
serial_out
Text Label 7250 3950 0    50   ~ 0
serial_in
Wire Wire Line
	5900 3800 6500 3800
Wire Wire Line
	6500 3800 6500 3950
Wire Wire Line
	6500 3950 7050 3950
Text GLabel 6100 5150 1    50   Input ~ 0
motor1_1
Text GLabel 6200 5150 1    50   Input ~ 0
motor1_2
Text GLabel 6300 5150 1    50   Input ~ 0
motor1_3
Text GLabel 6400 5150 1    50   Input ~ 0
motor1_4
Text GLabel 6500 5150 1    50   Input ~ 0
motor2_1
Text GLabel 6600 5150 1    50   Input ~ 0
motor2_2
Text GLabel 6700 5150 1    50   Input ~ 0
motor2_3
Text GLabel 6800 5150 1    50   Input ~ 0
motor2_4
Text GLabel 7000 5150 1    50   Input ~ 0
latch
Text GLabel 7100 5150 1    50   Input ~ 0
load
Text GLabel 7200 5150 1    50   Input ~ 0
clock
Text Label 6100 5350 3    50   ~ 0
pin2
Text Label 6200 5350 3    50   ~ 0
pin3
Text Label 6300 5350 3    50   ~ 0
pin4
Text Label 6400 5350 3    50   ~ 0
pin5
Text Label 6500 5350 3    50   ~ 0
pin6
Text Label 6600 5350 3    50   ~ 0
pin7
Text Label 6700 5350 3    50   ~ 0
pin8
Text Label 6800 5350 3    50   ~ 0
pin9
Text Label 7000 5350 3    50   ~ 0
pin11
Text Label 7100 5350 3    50   ~ 0
pin12
Text Label 7200 5350 3    50   ~ 0
pin13
$Comp
L Connector:Conn_01x12_Male J?
U 1 1 5C96829D
P 6600 5350
F 0 "J?" V 6527 5278 50  0000 C CNN
F 1 "conn_arduino" V 6350 5350 50  0000 C CNN
F 2 "" H 6600 5350 50  0001 C CNN
F 3 "~" H 6600 5350 50  0001 C CNN
	1    6600 5350
	0    -1   -1   0   
$EndComp
Text GLabel 6900 5150 1    50   Output ~ 0
serial_out
Text Label 6900 5350 3    50   ~ 0
pin10
$EndSCHEMATC
