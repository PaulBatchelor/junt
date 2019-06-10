(defn param [p]
  (if (string? p)
      (rvl (string "\"" p "\""))
      (rvl (string p))))

# use say to print string
(param "hello world")
(rvl "say")
# use 'p' to print number
(param 1234)
(rvl "p")
