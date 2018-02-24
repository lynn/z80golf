# Z80Golf

This is a mirror of mokehehe's Z80 code golf machine, which I've documented on [esolangs](https://esolangs.org/wiki/Z80golf). Here is a translation of `README.txt`:

> ## Z80Golf Environment
>
> ### make
> Run `make` in the `src` directory to obtain the `z80golf` executable.
>
> ### Execution
> Supply the `.z8b` files in the `test` directory to execute them.
>
>     z80golf helloworld.z8b
>     z80golf echo.z8b < echo.asm
>     z80golf fizzbuzz.z8b
>
> ### z80golf conventions
> 
> - The supplied binary is placed at the zero address.
> - The program is terminated by `HALT` (`76H`).
> - If you call `8000H` the contents of the A register are printed to `stdout` as a single character.
> - If you call `8003H` a character is read [into A] from `stdin`. The carry flag is set to signal EOF.
>
> ### Miscellaneous
>
> Uses fMSX's Z80 emulator. http://fms.komkon.org/fMSX/
> 
> I hear the license to use its source code is to be obtained by e-mail. [?]

I'm not sure what mokehehe means by the final line. I downloaded fMSX, and it comes with this note:

> fMSX source code is open for everyone to see but it is not in public domain. You can look and learn from it, but you cannot change it or copy it without giving a credit to the original author and a few other conditions. If you would like to port fMSX to another platform or make changes to the code, please, contact me by email or some other means.

But those "few other conditions" are nowhere specified. That said, none of this is for commercial purposes; I'm only keeping this here for the purpose of archival.

