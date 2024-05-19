class ExceptionHandler(object):
    """ Object that handles proper exception throwing, with useful error info """

    def __init__(self, lexer, consolePrompt=">> "):
        self.lexer = lexer
        self.console_prompt = consolePrompt
        self.source_file_path = None

    def setSourceFilePath(self, source_file_path):
        self.source_file_path = source_file_path

    def raiseException(self, error_message):
        exception_message = "\n" + self.console_prompt

        if self.source_file_path != None:
            exception_message += "EXCEPTION at " + self.source_file_path + ", line " + str(self.lexer.lineno) + ":\n\t"

        print(exception_message + self.console_prompt + error_message)

        exit()
