# maze-bot
Projects and code for the robot made for the maze solving competition Robocup Jr 2017.

## Todo

By Thursday:
- [ ] Turn on a LED when a victim has found
- [ ] Change Ultrasonic disposition (the one on the back goes on front)
- [ ] Gyroscope compensation from temperature variations

Long term:
- [ ] Debug in every object with a define in maze-bot.ino
- [x] Debug over bluetooth
- [ ] Desktop GUI for testing

## Notes

To import libraries to your IDE you have to create a symlink from this repository to your Arduino libraries folder. To do that you need first to delete the defalut arduino libraries folder, then to open an administrator command prompt and give the following command:

mklink /J ArduinoLibrariesFolder YoutGitHub\maze-bot\libraries
