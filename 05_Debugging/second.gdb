set pagination off
set logging overwrite
set logging redirect
set logging file ./second.log
set logging on

b 35 if 28 <= i && i <= 35
commands
    output {m, n, s, val}
    c
end

r
q