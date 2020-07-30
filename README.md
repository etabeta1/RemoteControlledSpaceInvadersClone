# RemoteControlledSpaceInvadersClone
A wifi contolled Space Invaders clone made for Arduino and NodeMCU.

The NodeMCU creates a WiFi network and will listen to http request, depending on the request, it will turn HIGH or LOW some wires, the Arduino will detect the state of the wires and move the spaceship or shoot a bullet according to the state.
The http requests gan be generated from everything connected to the WiFi of the NodeMCU but is suggested to insert a 15ms delay between the requests. You can use the Android App to control the game.
The Arduino uses the TVOut library to generate a composite video signal.

# list of the requests
  - 192.168.1.1/0 -> nothing
  - 192.168.1.1/1 -> move left
  - 192.168.1.1/2 -> move right
  - 192.168.1.1/3 -> move left and right = nothing
  - 192.168.1.1/4 -> shoot
  - 192.168.1.1/5 -> shoot and move left
  - 192.168.1.1/6 -> shoot and move right
  - 192.168.1.1/7 -> shoot and move left and right = shoot
