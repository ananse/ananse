dim i as integer
dim k as integer

for i = 0 to 10 step 2
    print i
    if i = 5 then
        exit for
    else
        continue for
    end if
next

while k < 10
    k = k + 1
    continue while
wend

do 
    print 'Hello World'
loop while i = 6

function random() as integer
    print 'A random number'
end function

print 'Dead'
