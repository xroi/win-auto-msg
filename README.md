# win-auto-msg

A minimal C++ application for automatic sending
of [windows messages](https://learn.microsoft.com/en-us/windows/win32/learnwin32/window-messages) to
background/foreground windows.

**This project is still a work in progress**

## Demo

![](https://github.com/xroi/win-auto-msg/blob/master/assets/demo.gif)

## General Information

In windows, communication with applications is done by passing messages to them. A message is simply a numeric code that
designates a particular event. For example, if the user presses the left mouse button, the window receives a message
that has the following message code.

```
#define WM_LBUTTONDOWN    0x0201
```

Usually, that message is sent to the foreground window. This application allows
sending messages to any open window. This is useful for any type of automation or testing.

## Features

- Send automated keyboard and mouse messages to chosen background/foreground windows. 
- Pick from a list all valid open top windows (Messages are sent to top window and all child windows).
- Mouse locator utility for finding mouse coordinates.

## Planned Features

- [ ] script parsing
- [ ] wake preempted background processes?
- [ ] enable choosing a single subwindow.
- [ ] add sendKey overload to take multiple keys at once, then at script parsing optimize so that it uses that.
- [ ] "recording" mode into scripts
- [ ] prevent user effect of shift/ctrl keys on background windows

## Script files

Win-auto-msg allows using text files to script the automation. The following is a guideline to the format of these
files. Note that these files only allow basic automation (`press`, `type`, `sleep` and `loop`). For more advanced
scripting, consider implementing C++ code that uses the API.

### press

The basic `press` command in these files is defined with a button identifier, followed by a space, followed by a
duration in seconds. For example, if we want the script to press the A key on the keyboard for 3 seconds, we would
write:

```
press KEY_A 3
```

Note that in practice this command will be translated to 2 messages, a down and an up command.

A button can also be pressed indefinitely (i.e. by only issuing a down command) by using a `*` for the duration.

```
press KEY_A *
```

A button can also be "tapped" (i.e. down for small constant of time) by using a `.` for the duration. This is useful for
typing/clicking tasks.

```
press KEY_A .
```

The case for mouse commands (`KEY_LBUTTON`, `KEY_RBUTTON`, `KEY_MBUTTON`,`MOUSEMOVE`) is a little different, since we
need to specify the mouse coordinates. The following line will press the left mouse button, for 0.5 seconds, at
coordinates (100, 200).

```
press KEY_LBUTTON 0.5 100 200
```

Note that the mouse coordinates are not relative to the screen, but to the window itself.

### type

The type command allows a line of text to be organically typed. Think of it as shorthand for many press commands,
specifically for letters.

### sleep

The sleep command allows specifying a duration of time for which the script will sleep. During sleep, pressed button
timers that have already started will still progress and end, but the script itself will pause. For example, the
following script will press the A key for 5 seconds, and then press the B key for 2 seconds.

```
press KEY_A 5
sleep 5
press KEY_B 2
```

The reasoning behind this is to allow concurrent keypresses. For example, the following script will press the A key and
B key concurrently for 3 seconds. And then add the C key for an additional 2 seconds.

```
press KEY_A 5
press KEY_B 5
sleep 3
press KEY_c 2
```

### loop

The loop and endloop command allows a section of the script to repeat multiple times. For example, the following script
will press the A key for 1 second once every 2 seconds.

```
loop
press KEY_A 1
sleep 2
endloop
```

## References & Acknowledgements

- [win32 Messages API](https://learn.microsoft.com/en-us/windows/win32/learnwin32/window-messages)
- [Keyboard](https://github.com/EasyAsABC123/Keyboard)


