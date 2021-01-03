# Lexical Analyzer

Lexical analyzer is a C++ console application for windows, used to write a report of a script file depending on given language definition file in XML format.

## How to use

You can start the application via either opening the executable file (LexicalAnalyzer.exe) or by opening it via command prompt and giving it appropriate arguments.

There are three arguments you can pass to the application:
| Syntax | Description |
| ---------- | -----------|
| -l | the given file after this parameter is a language XML file | 
| -o | the given file after this parameter is a desired output file |
| -i | the given file after this parameter is an input script file |

Here are some examples of running the application through a command prompt with arguments:

- `.\LanguageAnalyzer.exe -o outputFilename.txt`
- `.\LanguageAnalyzer.exe -i testcase.txt -o testResults.txt`
- `.\LanguageAnalyzer.exe -l language.xml -i whatever.txt`

The order at which you specify these arguments does not matter and any missing arguments is going to force the application to prompt the user to enter missing files.

## Language definition file

Language definition file is defined using the XML syntax. 
There are six main elements:
1. `<language>` : the root element, there may only be one.
2. `<category>` : goes inside `<language>` element, there can be multiples, but two categories must exist and they must have a type attribute.
   - The required category types (attributes) are: `"separators"` and `"comments"`.
3. `<whitelist>` : goes inside `<category>` element, is used to denote that elements inside of it belong to a whitelist behaviour.
4. `<blacklist>` : goes inside `<category>` element, is used to denote that elements inside of it belong to a blacklist behaviour.
5. `<string>` : goes inside either `<whitelist>` or `<blacklist>` elements, specified text is meant to be found exactly as is. 
    - However, the given string still has to follow RegEx syntax rules.
6. `<expression>` : goes inside either `<whitelist>` or `<blacklist>` elements, specified expression is used for `regex_match()` method.

For RegEx syntax rules, please refer to [RegEx syntax](http://userguide.icu-project.org/strings/regexp)

### Blacklisting and Whitelisting

Blacklists will match given string to its category only if it doesn't match with any of the elements inside the blacklist.

Whitelist will match the given string to its category if it matches with any of the elements inside the whitelist.

It is possible to combine blacklists and whitelists in a single category, at then, it will check through the whitelist elements, and then check the blacklist elements.

## Language definition file - example

```XML
<?xml version="1.0" encoding="utf-8" standalone="no" ?>
<language>
  <category type="separators">
    <whitelist>
      <string>\s</string> <!--whitespace-->
    </whitelist>
  </category>

  <category type = "comments">
    <whitelist>
      <string>\$</string>
      <expression>\$.*</expression>
    </whitelist>
  </category>

  <category type = "identifiers">
    <blacklist>
      <expression>\(.*</expression>
    </blacklist>
  </category>

  <category type = "operators">
    <whitelist>
      <string>+<string>
    </whitelist>
  </category>

```

For an XML format cheatsheet, please refer to [XML Syntax Rules](https://www.ibm.com/support/knowledgecenter/SSRJDU/reference/SCN_XML_Syntax_Rules.html).