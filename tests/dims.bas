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

function random(seed as integer) as integer
    print 'A random number'
end function

do 
    print 'Hello World'
    random(2)
loop while i = 6

print 'Dead'
