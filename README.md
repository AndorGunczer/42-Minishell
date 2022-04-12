# Minishell
This project intends to recreate a shell from scratch following Bash Documentation as a guideline

It is a highly advanced shell which can handle the following:
  - Any input is handled without leaks or crash or undefined behaviour.
  - Program handles absolute path as well as complex/overcomplicated relative paths
  - Redirections work as in bash (<,<<,>,>>)
  - Pipes, pipelines work similarly to bash (|) - Pipelines and Redirections can be chained together.
  - Core builtins programmed into the project manually.
  - Exit Status and Expansion of variables handled
  - Signal Handling identical to bash
  - History implementation
  - Nice handling of single and double quotes

How to make it work:
  1. Clone repository
  2. Make in Project root directory
  3. Launch executable (./minishell)
  4. Enjoy!
