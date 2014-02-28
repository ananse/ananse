dim i as integer = 6

function say_hello() as integer
    print 'Hello'
    return 5
end function

function add(a as integer, b as integer) as integer
    return a+b
end function

do 
    i = add(6,7)
    print i
loop while i = 6
