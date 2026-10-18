# Project1_NaySanHtut

## Build and Run

```
g++ -Wall -std=c++11 -o capacitor capacitor.cpp
./capacitor
```

## Equations

**Constant current source**

```
V(t+1) = V(t) + I(t) * dt / C
```

Initial condition: `V(0) = 0`

**Constant voltage source with series resistor**

```
I(t+1) = I(t) - I(t) * dt / (R*C)
V(t+1) = V(t) + I(t) * dt / C
```

Initial conditions: `V(0) = 0`, `I(0) = V0 / R`

## Parameters

| Parameter | Value |
|---|---|
| Time step, dt | 1e-10 s |
| Final time | 5e-6 s |
| Number of time steps | 50000 |
| Resistance, R | 1 kOhm |
| Capacitance, C | 100e-12 F |
| Source current (constant current) | 1e-2 A |
| Source voltage, V0 (constant voltage) | 10 V |

## Output

The program prints step, time, voltage and current every 200 timesteps for each circuit:

```
Constant current source (I = 1e-2 A)
  step        time (s)     voltage (V)     current (A)
     0    0.000000e+00    0.000000e+00    1.000000e-02
   200    2.000000e-08    2.000000e+00    1.000000e-02
   ...

Constant voltage source (V0 = 10 V, R = 1 kOhm)
  step        time (s)     voltage (V)     current (A)
     0    0.000000e+00    0.000000e+00    1.000000e-02
   200    2.000000e-08    1.813512e+00    8.186488e-03
   ...
```
