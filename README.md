#Clever Models

Small tool to generate POJOs model classes from  Feeds. ( JSON  ) .

Current Support, Java, C# & Objective-C models from JSON Feeds.

###Install : 

- ``` git clone git@github.com:BrunoAlexandreMendesMartins/CleverModels.git```
- ```$ cd CleverModels/Release```
- ```$ make ```

###Usage : 

- ``` ./cm -n [Name of Initial Class Model] -p [folder path to where to write the models] -l [programming language] -u [Feed URL] ```

Example:

``` ./cm -n Result -p ~/Downloads/models/ -l java -u http://www.mocky.io/v2/5b238b972f00007a00e095c7 ```

### Others:

-h [string to write to headers]. - For example: package com.somepackage.name

Supported Language arguments

-l java
or
-l' objc
or
-l csharp
