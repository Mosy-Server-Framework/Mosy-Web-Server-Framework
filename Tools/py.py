file_object = open('txt.txt','rU')
file_obj = open('out.txt','a')
try: 
    for line in file_object:
         lis = line.split("\t")
         file_obj.write('FileTypes.insert_or_assign(L"' + lis[0] + '", L"' + lis[1] + '");\n')
finally:
     file_object.close()
     file_obj.close()