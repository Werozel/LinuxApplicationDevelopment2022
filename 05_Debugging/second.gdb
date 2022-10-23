set pagination off
set logging overwrite
set logging redirect
set logging file ./second.log
set logging on

b 35 if i <= 35 - 28
commands
    output {m, n, s, val}
    c
end

r
q