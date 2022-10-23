set pagination off
set logging overwrite
set logging redirect
set logging file ./first.log
set logging on

b 35 if val % 5 == 0
commands
    output {m, n, s, val}
    c
end

r
q
