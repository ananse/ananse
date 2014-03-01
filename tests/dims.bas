dim i as integer = 6

sub say_hello()
    print 'Hello'
end sub

function add(a as integer, b as integer) as integer
    return a+b
end function

do 
    i = add(6 ,add(2,2))
    print i
    say_hello()
loop while i = 6
