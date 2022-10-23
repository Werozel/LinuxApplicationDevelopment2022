set pagination off
set logging file ./first.log
set logging on

b 35 if i % 5 == 0
commands
    output {m, n, s, val}
    c
end

r
q
