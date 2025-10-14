# 🚨 Pre-Programming Checklist - ATmega32 Navigation Bot

## ⚠️ **CRITICAL - Programming से पहले ये सब CHECK करें!**

### 1. 🔌 **Power Supply Check**
```
□ 12V supply connected और stable है
□ 7805 regulator properly connected
□ 5V output measured और verify किया
□ All ground connections common हैं
□ Polarity सही है (+ve, -ve properly connected)
```

### 2. 🖲️ **ATmega32 Connections**
```
□ VCC (Pin 40) = +5V measured
□ GND (Pins 20, 21, 30) = 0V measured  
□ AREF (Pin 31) = +5V connected
□ RESET (Pin 1) = +5V through 10kΩ resistor
□ 16MHz crystal properly connected to XTAL1, XTAL2
□ 22pF capacitors on both crystal pins to GND
```

### 3. 🔗 **USBasp Connection Check**
```
□ USBasp power LED ON
□ ISP header pins properly connected:
   - MISO → PB5 (Pin 17)
   - MOSI → PB4 (Pin 16) 
   - SCK  → PB6 (Pin 18)
   - RESET → Pin 1 (through resistor)
   - VCC  → +5V
   - GND  → GND
□ No loose connections in ISP cable
```

### 4. 💻 **Computer Setup**
```
□ Microchip Studio installed
□ USBasp drivers installed (using Zadig)
□ USBasp detected in Device Manager
□ Project files properly located
```

### 5. 🖥️ **LCD Connections Verify**
```
□ VSS (Pin 1) → GND
□ VDD (Pin 2) → +5V  
□ V0  (Pin 3) → GND (for contrast)
□ RS  (Pin 4) → PB0
□ EN  (Pin 5) → PB1
□ D4  (Pin 11) → PD4
□ D5  (Pin 12) → PD5
□ D6  (Pin 13) → PD6
□ D7  (Pin 14) → PD7
□ Backlight: A(+5V), K(GND)
```

### 6. 📡 **Sensor & Motor Connections**
```
□ HC-SR04: VCC(+5V), GND(0V), Trig(PC0), Echo(PC1)
□ Servo: Red(+5V), Black(GND), Orange(PB3)
□ L298N: Logic power +5V, Motor power +12V
□ LED: Anode through 220Ω to PA6, Cathode to GND
□ All motor connections as per diagram
```

## 🔥 **DANGER - ये गलती बिल्कुल न करें!**

### ❌ **Power Supply Mistakes:**
```
✗ 12V directly to ATmega32 (WILL DAMAGE!)
✗ Reverse polarity connection
✗ No common ground between supplies
✗ Weak or unstable power supply
```

### ❌ **Programming Mistakes:**
```
✗ Wrong crystal frequency setting (must be 16MHz)
✗ Wrong fuse settings 
✗ USBasp connected while circuit is powered separately
✗ Short circuits in ISP connections
```

### ❌ **Circuit Mistakes:**
```
✗ Cross connections between pins
✗ Missing ground connections
✗ Wrong pin assignments
✗ 5V and 12V mixed up
```

## ✅ **Step-by-Step Safe Programming Process**

### **Phase 1: Hardware Verification**
1. **Power OFF** - Disconnect all power
2. **Check continuity** with multimeter
3. **Verify pin connections** with circuit diagram
4. **Check for short circuits** between VCC and GND

### **Phase 2: Power-On Testing**
1. **Connect 12V supply** (motors disconnected)
2. **Measure 5V output** from 7805
3. **Check ATmega32 VCC pin** = 5V
4. **Verify all ICs getting proper power**

### **Phase 3: USBasp Connection**
1. **Power OFF the circuit**
2. **Connect USBasp to ISP header**
3. **Connect USBasp to computer**
4. **Power ON circuit through USBasp** (circuit should not have separate power)

### **Phase 4: Programming**
1. **Open Microchip Studio**
2. **Open navigation_bot.atsln**
3. **Build project** (F7)
4. **Check for compilation errors**
5. **Tools → Device Programming**
6. **Select ATmega32 and USBasp**
7. **Set fuses**: Low=0xFF, High=0xC9
8. **Program flash memory**

### **Phase 5: Testing**
1. **Disconnect USBasp**
2. **Connect separate 12V power supply**
3. **Power ON and test**

## 🧪 **Testing Sequence After Programming**

### **Test 1: LCD Display**
```
Expected: "Navigation Bot" then "Initializing..." then "Status: READY"
If not working: Check LCD connections, power, contrast
```

### **Test 2: LED Indicator** 
```
Expected: LED should be OFF initially
Test: Put obstacle in front - LED should turn ON
```

### **Test 3: Servo Movement**
```
Expected: Servo should center initially, then scan when obstacle detected
Check: Smooth 90° rotation left and right
```

### **Test 4: Motor Response**
```
Expected: Motors move forward initially
Test: Should stop when obstacle detected, turn after scanning
```

## 📞 **Troubleshooting Quick Fixes**

### **Problem: Programming Failed**
```
□ Check USBasp drivers
□ Verify ISP connections  
□ Check power supply to circuit
□ Try different USB port
□ Check crystal oscillator connections
```

### **Problem: LCD Not Working**
```
□ Check 4-bit data connections (PD4-PD7)
□ Verify RS (PB0) and EN (PB1) connections
□ Confirm V0 connected to GND for contrast
□ Check power supply to LCD
```

### **Problem: Motors Not Moving**
```
□ Check 12V supply to L298N VIN
□ Verify motor driver connections
□ Check enable pins (PA2, PA5)
□ Test with separate motor power supply
```

### **Problem: Servo Not Moving**
```
□ Check PWM connection to PB3 (OC0 pin)
□ Verify servo power supply (+5V)
□ Check servo mounting and mechanical freedom
```

## 🎯 **Final Pre-Programming Checklist**

```
□ All connections double-checked with multimeter
□ Power supply voltages verified (5V, 12V)
□ No short circuits detected
□ USBasp drivers installed and working
□ Project compiles without errors in Microchip Studio
□ ISP connections secure and correct
□ Circuit powered properly during programming
□ Fuse settings configured for 16MHz crystal
□ All components mounted securely
□ Ready for safe programming!
```

**Remember: एक बार programming हो जाए, तो carefully testing करें और फिर enjoy करें आपका navigation bot! 🚀**