#!/usr/bin/python3

#TODO improve modularity of code

import sys

if len(sys.argv) < 2:
    print('Please specify file name')
    exit(1)

filename = sys.argv[1]

filename_without_extension = filename.split('.')[0]

extension = filename.split('.')[-1]

classname = filename_without_extension.split('/')[-1]

# Getting header and source filename
if extension == 'hpp':

    hdrfilename = filename
    srcfilename = filename.replace('include', 'src')
    srcfilename = srcfilename.replace('hpp', 'cpp')

elif extension == 'cpp':

    srcfilename = filename
    hdrfilename = filename.replace('src', 'include')
    hdrfilename = hdrfilename.replace('cpp', 'hpp')

lines = [line.rstrip('\n') for line in open(hdrfilename)]

inclass = False

# Trailing means there is an implimentation in the header file
# which is still going on the current line
trailing = False
template = False

methods = []
functions = []

i = 0
while i < len(lines):
    line = lines[i]
    i += 1

    if line.find('template') != -1:
        template = True

    if line.find('class') != -1 or line.find('struct') != -1:
        inclass = True
    else:
        # Method / function may already be implemented
        # Trailing means we are inside an implimentation
        if line.find('{') != -1:
            trailing = True

    if line.find('}') != -1:

        if trailing:
            trailing = False

        elif inclass:
            inclass = False

        if template:
            template = False

    if not trailing:
        if line.find('(') != -1:
            # Found potential impl target

            # Remove keywords
            line = line.replace('static ', '')
            line = line.replace('\t', '', 1)
            line = line.replace('    ', '', 1)
            line = line.replace('virtual ', '')

            method = []
            while line.find(')') == -1:
                # The method / function declaration is a few lines long
                method.append(line)
                line = lines[i]
                i = i + 1

            # Remove ;
            line = line.rstrip(';')
            method.append(line)

            # Check if method pure virtual or default or delete
            if line.find('=') == -1:
                if inclass:
                    # Add classname:: in front of methods
                    start_paren =  method[0].find('(')
                    start_method_name = method[0].rfind(' ', 0, start_paren - 1)
                    if start_method_name == -1:
                        method[0] = classname + '::' + method[0]
                    else:
                        start_method_name = start_method_name + 1
                        method[0] = method[0][:start_method_name] + classname + '::' + method[0][start_method_name:]
                    # Add template specific template
                    if template:
                        method[0] = "template <typename T> " + method[0]
                        method = [line.replace(classname, classname + "<T>") for line in method]
                    methods.append(method)
                else:
                    # Add template specific template
                    if template:
                        method[0] = "template <typename T> " + method[0]
                        template = False
                    functions.append(method)

# We got everything we need from the header file


# Working in source file
# In case file non existent, create it
try:
    srcfile = open(srcfilename, "a+")
    srcfile.close()
except IOError:
    print('Couldn\'t open file', srcfile)
    exit(1)

# Here we know file exists
srcfile = open(srcfilename, "r")

lines = [line.rstrip('\n') for line in srcfile]

# If already implemented, don't implement

implmethods = methods
implfunctions = functions

for line in lines:
    for method in methods:
        if line.find(method[0]) != -1:
            implmethods.remove(method)
    for function in functions:
        if line.find(function[0]) != -1:
            implfunctions.remove(function)

srcfile.close()
srcfile = open(srcfilename, "a")

# Write implimentation to file

for i in range(0, len(methods) - 1):
    for j in range(0, len(methods[i]) - 1):
        srcfile.write('\n' + methods[i][j])
    srcfile.write('\n' + methods[i][-1] + ' {}\n')

if (len(methods) > 0):
    for j in range(len(methods[-1]) - 1):
        srcfile.write('\n' + methods[-1][j])
    srcfile.write('\n' + methods[-1][-1] + ' {}\n')

for i in range(0, len(functions) - 1):
    for j in range(0, len(functions[i]) - 1):
        srcfile.write('\n' + functions[i][j])
    srcfile.write('\n' + functions[i][-1] + ' {}\n')

if (len(functions) > 0):
    for j in range(0, len(functions[-1]) - 1):
        srcfile.write('\n' + functios[i][j])
    srcfile.write('\n' + functions[-1][-1] + ' {}\n')
