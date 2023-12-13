/*==============================================================================
 File: Simple-Robot.c               Activity: mirobo.tech/chrp4-starter-1
 Date: December 12, 2023
 
 CHRP4 simple robot starter program. Create your own line-following robot by
 modifying this starter program. It uses either digital or analog light sensing,
 and digital or analog motor control. Follow the steps in the Program Analysis
 Activities below the program code to test your robot's light sensors, connect
 the motors and configure their output pins, and create basic line-following
 robot programs. Optimize your program afterwards for more reliable performance
 and to add additional features.
 
 To complete this activity, you will need: a CHRP4 circuit board assembled in
 the line-following configuration (see https://mirobo.tech/assembling-chrp4)
 and ideally installed in a completed robot base with an infrared (IR) LED, two
 phototransistors, and two DC motors. See https://mirobo.tech/simple-robo for
 an example of a simple line-following robot design showing the installation
 mounting details of the optical line sensor components.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "CHRP4.h"           // Include CHRP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// Operating mode definitions
#define digital 0               // Digital line following mode
#define analog  1               // Analog line following mode

// Light sensor digital level definitions
#define light   0               // Light sensor is illuminated
#define dark    1               // Light sensor is dark

// Variable definitions
unsigned char mode = digital;   // Start in digital line-following mode
unsigned char lightLevelLeft;   // Left sensor light level
unsigned char lightLevelRight;  // Right sensor light level

// LATC motor output constants. The four most sifnificant LATC bits control both 
// motors as well as the D2-D5 LEDs. Change these bits to set the motor
// direction. Leave the two least significant bits set to ensure floor LEDs
// D6-D8 stay lit and the phototransistor circuits remain energized. If using
// the 'fwd' motor constant causes either of your motors to run in reverse,
// either swap that motor's wires on the CON1 motor header, or change swap the
// pairs of output bits in the code, below: (e.g. 0b10... to 0b01... will change
// the direction of motor 2)
const char stop = 0b00000011;   // Both motors off, floor sensor LEDs on
const char fwd = 0b10010011;    // Both motors forward, floor sensor LEDs on
//const char rev                  // TODO - Add constants for all required directions
//const char left
//const char fwd_left
//const char rev_left
//const char right
//const char fwd_right
//const char rev_right

int main(void)
{
    OSC_config();               // Configure oscillator for 48 MHz
    CHRP4_config();             // Configure I/O for on-board CHRP4 devices
    
    D6 = 1;                     // Turn line sensor LED on
    
    // Light sensor test code
    while(1)
    {
        if(Q1 == 1)             // Check if Q1 sees dark
        {
            D2 = 1;
        }
        else
        {
            D2 = 0;
        }
        
        if(Q2 == 1)             // Check if Q2 sees dark
        {
            D5 = 1;
        }
        else
        {
            D5 = 0;
        }
        
        // Reset the microcontroller and start the bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
            
    while(1)
    {
        while(mode == digital)
        {
            if(Q1 == dark && Q2 == dark)    // If both sensors see the line...
            {
                LATC = fwd;     // Drive both motors forward
            }
            else if(Q1 == dark && Q2 == light)  // If only Q1 sees the line...
            {
                // TODO - Determine direction to drive in
            }
            // TODO - Add additional light sensor checks and motor output code
            
            // Reset the microcontroller and start the bootloader if SW1 is pressed.
            if(SW1 == 0)
            {
                RESET();
            }
        }
    }
}

/* Learn More -- Program Analysis Activities
 * 
 * 1.   After assembling your CHRP4 circuit board into your robot chassis and
 *      installing the optical line sensor components, the next step should be
 *      to test these components and ensure that they can distinguish between
 *      light and dark surfaces. The first while(1) loop in the main part of
 *      this starter program is temporary code that does just that. It first
 *      lights the line sensor LED (LED D6), and then reads and displays the
 *      light levels from the Q1 and Q2 phototransistors using LEDs D2 and D5.
 *      Note that D6 is an infrared (IR) LED, so you won't be able to see the
 *      light produced by it, but the phototransistors should see the light from
 *      D6 reflected by white or light-coloured surfaces below them.
 *      
 *      Compile the program and download it into your CHRP4. Create a test
 *      target using a white surface with a thick (approx. 1cm wide) black
 *      marking on it. You can create this target using a black marker on paper,
 *      or by applying black electrical tape onto a white surface. Set your
 *      robot on the target and move its sensors over the white and black areas
 *      while running the program. LEDs D2 and D5 should light to indicate when
 *      the phototransistors see the black or dark areas of the target.
 * 
 *      If the LEDs don't light up when the sensors are over the black areas,
 *      check the installation height of both the LEDs and phototransistors,
 *      ensure their solder connections are good, and confirm that you have
 *      installed them into the CHRP4 circuit in their proper orientation. A
 *      voltmeter can be used to check the potential across D6 to ensure it is
 *      lit. If D6 is operating properly, the meter should read around 1.1V.
 * 
 *      A voltmeter can also be used to check the voltage drops across Q1 and Q2
 *      as you bring them close to a white reflective surface. The potential
 *      should drop as the phototransistors see more reflected light.
 * 
 *      After testing both of your sensors and ensuring that they are working,
 *      continue by examining the program code. The 'if' statements are used to
 *      detect light or dark, and to turn on the appropriate LED when each
 *      phototransistor senses dark.
 * 
 *      Each if statement used in the program checks for a high voltage level,
 *      or logic 1. Why do you think that the phototransistor outputs will be a
 *      higher voltage when exposed to dark, and a low voltage when exposed to
 *      light? (Hint: refer to the schematic to determine how they they are
 *      connected in the circuit.)
 * 
 * 2.   Now that we have characterized the operation of the phototransistors
 *      in this circuit, we can make it easier for us and others to modify the
 *      program in the future by creating definitions for the expected light
 *      levels. The definitions have already been added at the top of the
 *      program, and are repeated here for reference:

// Light sensor digital level definitions
#define light   0               // Light sensor is illuminated
#define dark    1               // Light sensor is dark

 *      Change your test program to use the light and dark definitions in the
 *      if statements and verify that your program works. These definitions will
 *      be used in the next section of the program to help to make the code more
 *      easily understandable by than using 0 and 1 in the condition statements.
 * 
 * 3.   With the light sensors tested and working, the next step is testing the
 *      motor outputs and configuring the motor directions. If you haven't done
 *      so already, connect the two wires of the left motor to the M1 terminals
 *      and the two right motor wires to the M2 terminals of your CHRP4.
 * 
 *      Next, modify the code at the beginning of the main() function to add
 *      the LATC output instruction, while loop, and RESET() function call below
 *      the D6 = 1; statement as shown below. This will set the motor outputs
 *      to a specific value while ignoring any sensor inputs other than waiting
 *      for the reset button to be pressed:
    
    D6 = 1;                     // Turn line sensor LED on
    LATC = fwd;
    while(SW1 == 1);
    RESET();
    
 *      The 'fwd' constant used in the LATC statement was defined by this 
 *      statement, above the main program code:

const char fwd = 0b10010011;    // Both motors forward, floor sensor LEDs on

 *      Refer to the CHRP4 schematic to examine the PORTC (RC0-RC7) connections.
 *      PORTC connects to the floor LEDs and phototransistors, as well as the
 *      motor driver and D2-D5 LEDs. Each motor is driven by a pair of outputs,
 *      each of which can provide either a positive or ground potential to each
 *      of the two motor wires, resulting in four possible motor states:
 * 
 *      00 - motor off (both motor outputs grounded, or: -,-)
 *      01 - motor rotating in one direction (motor outputs: -,+)
 *      10 - motor rotating in the opposite direction (motor outputs: +,-)
 *      11 - motor off (motor outputs: +,+)
 * 
 *      The two highest order bits connect to M2, the right motor, and the next
 *      two bits connect to M1, the left motor. Assuming the motors are wired
 *      and connected the same way, the pre-defined 'fwd' motor constant drives
 *      the right motor in one direction using the value '10', and the left 
 *      motor in the opposite direction using the value '01'. Since the left and
 *      right motors are located on the opposite sides of the robot, these 
 *      constants should make the motors drive the robot in either the forward
 *      or reverse direction if your motors are wired in the same way.
 * 
 *      If your robot drives forward, you're all set to move on to defining
 *      the other motor constants in the next step.
 * 
 *      If your robot drives reverse, you have two choices: either swap each of
 *      the motor wire connections on the terminal strip, or re-define the 'fwd'
 *      constant to reverse the output bit pairs, like this:

const char fwd = 0b01100011;    // Both motors forward, floor sensor LEDs on

 *      If one motor drives forward, and the other reverse, swap the wires of
 *      the reverse motor to get it to drive forward.
 * 
 *      Hint for teachers and makerspace instructors: have all of your students
 *      or participants wire their motors the same way so that it's easier for
 *      students to work together on programming and to share the same code.
 * 
 * 4.   Complete the motor direction definitions for all possible driving
 *      directions. Assuming the values '10' in the first two bits of the 'fwd'
 *      motion definition drive M2 forward, changing these bits to '01' should
 *      drive M2 in reverse, while '00' will make M2 stop.
 * 
 *      Using three possible values for forward, reverse, and stop, for each of
 *      the two motors, your robot will be able to drive in up to 8 different
 *      directions. For example, there will be three possible ways to turn the
 *      robot left:
 * 
 *      Left (on the spot) - left motor in reverse, right motor forward
 *      Forward left - left motor stopped, right motor forward
 *      Reverse left - left motor stopped, right motor in reverse
 * 
 *      You will have to consider which type of turn is best for any particular
 *      application. A line following robot will be faster if it uses a forward
 *      left turn, for example, but an obstacle-sensing robot can turn faster
 *      using a left turn (on the spot), or more safely avoid an obstacle using
 *      a reverse left turn.
 * 
 *      Define the constants for all of the motor directions and try each one
 *      in your program to confirm its operation.
 * 
 * 5.   Once the light sensors have been tested and the motor outputs have been
 *      defined, it's time to put both the input and output code together to
 *      make a simple digital line-following robot. It's digital because it
 *      relies on digital control using an all-or-nothing response -- for each
 *      sensor input there will be a specific motor output.
 * 
 *      Remove the motor test code added in step 3 (leave the statement D6 = 1;)
 *      and then comment out the entire light sensor test code while loop. Your
 *      program's main while loop should now start with this code:

    while(1)
    {
        while(mode == digital)
        {
            if(Q1 == dark && Q2 == dark)    // If both sensors see the line...
            {
                LATC = fwd;     // Drive both motors forward
            }
            else if(Q1 == dark && Q2 == light)  // If only Q1 sees the line...

 *      As you can see, using the 'dark' and 'light' definitions makes the if
 *      statements much more readable. Complete the if condition statements
 *      for all four possible input combinations. You will need to decide on the
 *      best course of action to take when the robot goes off the line (if both
 *      phototransistors see light), but driving in reverse may be a good
 *      option to start with. You can explore more advanced options to improve
 *      your robot's line-following performance later.
 * 
 *      Complete the program code and test your robot on a simple track. You
 *      can make a track using black electrical tape applied to a white surface,
 *      or by drawing or painting a thick, black line on white paper.
 * 
 * 6.   If you watch the digital line-following robot make its way along a path,
 *      you will notice that it makes very deliberate motions, switching from
 *      forward, to turning, and back to forward again. These motions could be
 *      smoothed by using analog light sensing -- to determine much of the line
 *      each phototransistor sees -- coupled with PWM motor control to adjust
 *      the speed of each motor while providing more than simple on-off
 *      control. First, add the pwm_motors() function to your program above
 *      the main() code function:

// pwm_motors function - drive both motors at the specified speeds (0-255) using
// pulse-width modultation (PWM). If a motor runs in reverse, either swap the
// motor wires on the CON1 motor header or change the output pin in the code:
// e.g. swap M1A <-> M1B, or M2B <-> M2A
void pwm_motors(unsigned char lVal, unsigned char rVal)
{
    for(unsigned char t = 255; t != 0; t --)
    {
        if(lVal == t)
        {
            M1A = 1;
        }
        if(rVal == t)
        {
            M2B = 1;
        }
        __delay_us(5);
    }
    // End the pulses if PWM < 255
    if(lVal < 255)
    {
        M1A = 0;
    }
    if(rVal < 255)
    {
        M2B = 0;
    }
}

 *      This function is similar to the PWM code introduced in the Intro-3-Loops
 *      introductory activity. Next, add the analog-mode function, below, into
 *      the program's main while(1) loop:

        while(mode == analog)
        {
            // Read both floor sensors (darker = higher value)
            lightLevelLeft = ADC_read_channel(ANQ1);
            lightLevelRight = ADC_read_channel(ANQ2);

            // Drive motors by simple PWM using opposite light (dark) level
            pwm_motors(lightLevelRight, lightLevelLeft);

            if(SW1 == 0)            // Check S1 to re-start bootloader
            {
                RESET();
            }
        }

 *      This code simply reads the analog light level of each phototransistor
 *      and uses each sensor value as the speed setting for the opposite motor--
 *      with absolutely no if decisions required!
 * 
 *      Before the code can be used, the PORTC analog inputs have to be
 *      configured for operation, and the mode variable has to be set. Copy
 *      this code into the main() function, after the CHRP4_config() call:

    ADC_config();               // Configure Port C for analog inputs
    D6 = 1;                     // Turn line sensor LED on
    mode = analog;

 *      You should notice that the robot now follows the line more smoothly,
 *      but may get stuck in tight corners. 
 * 
 * 7.   Both the digital and analog program modes can be optimized for better
 *      performance. The digital mode could be improved by having the robot
 *      remember its last direction whenever it switches to a new direction so
 *      that it can 'undo' its last motion when it goes off the line. 
 *      
 *      The analog mode could be improved by scaling the limits of the PWM range
 *      to match the limits of the phototransistor input values, or by over-
 *      riding the PWM values when they are too low to efficiently drive the
 *      robot. Can you think of other ways to improve the program?
 * 
 *      Try to implement one or more modifications in your robot program code
 *      to improve its performance when following a line.
 * 
 * 8.   While a LATC statement has been used to output motor constants to the
 *      four motor port pins, a safer method of motor output uses logical
 *      operations to avoid over-writing the other PORTC pins. Since this
 *      would involve more than one line of code, it might be easier to
 *      implment this in its own function:

// motors function - safely send LATC motor constants only to motor I/O pins
void motors(unsigned char dir)
{
    LATC = LATC & 0b00001111;   // Reset LATC motor output pins
    LATC = LATC | dir;          // Write motor constant to motor outputs
}

 *      The motors() function uses the same direction constants that were
 *      defined for the LATC statement, but only modifies the four motor pins
 *      instead of re-writing the entire port. It can be called by your
 *      program like this:

        motors(fwd);

 * 9.   Another option that could be added to the robot program is mode
 *      switching between the digital and analog modes. Below is a version of
 *      the robot program implementing all of the changes from the prior steps
 *      of this activity, including the addition of a start-up mode selector.
 *      Can you add code to allow the robot to switch between modes while the
 *      robot is running, after the initial selection has been made?
 */

/*

// Operating mode definitions
#define digital 0               // Digital line following mode
#define analog  1               // Analog line following mode

// Light sensor digital level definitions
#define light   0               // Light sensor is illuminated
#define dark    1               // Light sensor is dark

// Variable definitions
unsigned char mode = digital;   // Start in digital line-following mode
unsigned char lightLevelLeft;   // Left sensor light level
unsigned char lightLevelRight;  // Right sensor light level

// LATC motor output constants. Four highest order LATC bits control motors and 
// D2-D5 LEDs ? change these bits to control motor direction. Leave two lowest
// order bits set to keep the D6-D8 LEDs lit up for line and floor sensing. If
// a motor runs in reverse, either swap the motor wires on the CON1 motor header
// or change the output pairs in the code, below: (e.g. 0b10... <-> 0b01...)
const char stop = 0b00000011;   // Both motors off, floor sensor LEDs on
const char fwd = 0b10010011;    // Both motors forward, floor sensor LEDs on
//const char rev                  // TODO - Add constants for all required directions
//const char left
//const char fwd_left
//const char rev_left
//const char right
//const char fwd_right
//const char rev_right

// motors function - safely send LATC motor constants only to motor I/O pins
void motors(unsigned char dir)
{
    LATC = LATC & 0b00001111;   // Reset LATC motor output pins
    LATC = LATC | dir;          // Write motor constant to motor outputs
}

// pwm_motors function - drive both motors at the specified speeds (0-255) using
// pulse-width modultation (PWM). If a motor runs in reverse, either swap the
// motor wires on the CON1 motor header or change the output pin in the code:
// e.g. swap M1A <-> M1B, or M2B <-> M2A
void pwm_motors(unsigned char lVal, unsigned char rVal)
{
    for(unsigned char t = 255; t != 0; t --)
    {
        if(lVal == t)
        {
            M1A = 1;
        }
        if(rVal == t)
        {
            M2B = 1;
        }
        __delay_us(5);
    }
    // End the pulses if PWM < 255
    if(lVal < 255)
    {
        M1A = 0;
    }
    if(rVal < 255)
    {
        M2B = 0;
    }
}

int main(void)
{
    OSC_config();               // Set oscillator for 48 MHz operation
    CHRP4_config();             // Set up I/O ports for on-board CHRP4 devices
        
    // Wait for a button press. SW3 starts digital line-following mode, SW4
    // starts analog line-following mode
    while(SW3 == 1 && SW4 == 1)
    {
        D1 = ~D1;               // Toggle LED D1
        __delay_ms(200);
        
        if(SW1 == 0)            // Check SW1 to re-start bootloader
        {
            RESET();
        }
    }
    D1 = 0;                     // Leave D1 on after switch press
    
    // Set mode
    if(SW3 == 0)
    {
        mode = digital;
    }
    else
    {
        ADC_config();           // Configure Port C for analog inputs
        mode = analog;
    }
    D6 = 1;                     // Turn line sensor LED on
    
    while(1)
    {
        while(mode == digital)
        {
            if(Q1 == dark && Q2 == dark)    // If both sensors see the line...
            {
                motors(fwd);        // Drive both motors forward
            }
            else if(Q1 == dark && Q2 == light)  // If only Q1 sees the line...
            {
                // TODO - Determine direction to drive in
            }
            // TODO - Add additional light sensor check and motor output code
            
            // Reset the microcontroller and start the bootloader if SW1 is pressed.
            if(SW1 == 0)
            {
                RESET();
            }
        }
        
        while(mode == analog)
        {
            // Read both floor sensors (darker = higher value)
            lightLevelLeft = ADC_read_channel(ANQ1);
            lightLevelRight = ADC_read_channel(ANQ2);

            // Drive motors by simple PWM using opposite light (dark) level
            pwm_motors(lightLevelRight, lightLevelLeft);

            // Reset the microcontroller and start the bootloader if SW1 is pressed.
            if(SW1 == 0)
            {
                RESET();
            }
        }
    }
}

 */