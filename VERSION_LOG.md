## Version Log

### **Current Version:** 1.6.2

- ##### 19/05/2024

  - Version 1.6.2 officially released!
    - Multi-line comments are back (hurray!)
    - Cleaned up some comments
    - Cleaned up some of the NucaScript 101 docs & Example code

- ##### 19/05/2024

  - Version 1.6.1 officially released!
    - Small `ExceptionHandler` message changes
    - Cleaned up some of the NucaScript 101 docs & Example code

- ##### 18/05/2024

  - Version 1.6.0 officially released!
    - Refactors most of the Compiler code
      - `nuca_script.py` had over 2.2k lines of code, which are now spread over multiple different files under the Compiler package
        - `Grammar.py` -> Contains all of the Formal Grammar rules and PLY functions that define NucaScript
        - `Utils.py` -> Contains useful methods that are found all over compiler code
      - Added new classes to easily manage dependencies
        - `Bootsrapper` -> Initializes all of the necessary values for building the lexer & parser
        - `Globals` -> An abstract class that contains global values to be used between multiple files
      - Improved python code import structure
        - Removed (almost) all of the `import *` statements, replacing them with newer python3 module import syntaxis
      - Small `ExceptionHandler` message changes & typo fixes
    - Some variable naming refactoring in VM code

- ##### 15/05/2024

  - Version 1.5.1 officially released!
    - Small compile time Exception bug fixes
      - Mentioning a method identifier (that was previously declared) without a set of () now raises the correct exception at compile time.
      - TODO: Still need to fix this for VOID type methods, since those do not currently have any reference in the SymbolTable at all.
    - Small README changes & typo fixes
    - New Sprint TODO ideas!

- ##### 02/01/2022

  - Version 1.5.0 officially released!
    - Revamps exception system and refactors most of the symbol & type lookup logic
      - Adds a brand new `ExceptionHandler` object, which takes care of relaying useful error messages on exceptions
        - _**Hurray**_ for line numbers on error messages!!
        - Program now exits gracefully on exceptions with a neat message followed by python's `exit()`, which looks cleaner on the console in comparison to the old `raise Exception()` jargon
      - Refactors lookup logic inside of `FunctionDirectory` in order to completely remove all `try / except` logic
        - Replaced it with `return` values and `if` statements, which got rid of about 80% of the indentation levels in each section
    - Small changes to how `#DEF` statements work with booleans
      - Previously coded them as an integer (either 0 or 1), now actually writes them down as `True` or `False`, which will ensure the correct type check when using its value in the code

- ##### 01/01/2022

  - **Happy New Year!!!**
  - Version 1.4.0 officially released!
    - Adds C-like `#DEF` statements for all basic data types!
      - Just like in C, these work by replacing the actual source code text with whatever value the definition name is coupled with
      - Currently, this **WILL** replace **ALL** instances of the definition name on the source code, **INCLUDING** those that are inside a string (within quotations)
        - PS: This behavior will be patched as soon as I figure out a _lazy_ way to get rid of it : )

- ##### 17/11/2021

  - Version 1.3.0 officially released!

    - Bug Fixes
      - Fixes a compile time bug that allowed for typed methods to be accepted even when their return method was contained inside an impossible conditional
        - This would cause all sorts of memory leaks on runtime, even though the program would compile with no error!
        - Typed methods now require not only that the last instruction of the method is a return statement with the correct type, but also that it is contained within the topmost conditional depth of the method's scope
        - PS: _else_ statements don't count as a conditional, so feel free to write return statements under those! (if you love yourself some redundancy :P )

- ##### 07/07/2021

  - Version 1.2.0 officially released!

    - Bug Fixes
      - Fixes major structural bug that threw compiler errors upon declaring global variables after a global method
      - Fixes type checking bug when using the result value of a class method on an arithmetical expression
    - New Ideas
      - Came up with new architectural ideas for object constructors; Stay tuned for future updates!

- ##### 04/06/2021

  - Version 1.1.0 officially released!

    - Bug fixes
      - Fixes compile time bugs caused by referencing class attributes inside of a method from a different class
      - Fixes bugs related to naming variables "t" + a numerical value, which conflicted with temporal names
      - Temporal names now start with a numerical value, which is not allowed for other IDS, resolving the conflict
    - Major changes to the _object_ type variables
      - Object variables must now specify their class type upon declaration, and cannot change afterwards
      - Object variables are now automatically instantiated upon entering their scope block (including object arrays)
      - Direct assignment to object variables is now disallowed, except for instantiations with the _new_ keyword.
      - _using as_ keyword removed!
      - Documentation updated to reflect these changes

- ##### 02/06/2021
  - Version 1.0.0 officially released!
