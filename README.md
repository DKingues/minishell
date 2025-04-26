# minishell
Minishell is a project for 42 School where you have to recreate your own bash.



COMMON INSTRUCTIONS:

• Your project must be written in C.

• Your project must be written in accordance with the Norm.

• Your functions should not quit unexpectedly (segmentation fault, bus error, dou-
  ble free, etc.).

• All heap-allocated memory must be properly freed when necessary.

• Makefile is necessary, must compile with flags and can't relink.

• To submit bonuses for your project, you must include a bonus rule in your Makefile.



INSTRUCTIONS:

• Display a prompt when waiting for command.

• Have a working history.

• Search and launch the right executable, based on the PATH variable or  using a relative absolute path.
  
• Use at most ONE GLOBAL VARIABLE to indicate a received signal.

• NOT interpret unclosed quotes or special characters not referred by subject ex: \ or ;.

• Single quotes ' should prevent shell from interpreting the meta characters in quoted sentence.

• Double quotes " should prevent shel from interpreting the meta characters in the quoted sentence exept for $.
  
• Implement the following redirections:
  < should redirect input.
  > should redirect output.
  << should be given a delimiter, then read the input until a line containing the delimiter is seen. It doesn’t have to update the history!
  >> should redirect output in append mode.
  
• Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.

• Handle environment variables ($ followed by a sequence of characters) which should expand to their values.

• Handle $? which should expand to the exit status of the most recently executed foreground pipeline.

• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.

• In interactive mode:
  ctrl-C displays a new prompt on a new line.
  ctrl-D exits the shell.
  ctrl-\ does nothing.
  
• Your shell must implement the following built-in commands:
  echo with option -n
  cd with only a relative or absolute path
  pwd with no options
  export with no options
  unset with no options
  env with no options or arguments
  exit with no options

• The readline() function may cause memory leaks, but you are not required to fix them.

