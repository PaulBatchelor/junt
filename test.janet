(defn param [p]
  (if (string? p)
      (rvl (string "\"" p "\""))
      (rvl (string p))))

(defn foo [] (print "hello foo"))

# use say to print string
(param "hello world")
(rvl "say")
# use 'p' to print number
(param 1234)
(rvl "p")

(def f (fiber/new (fn []
                       (print "hello 1")
                       (yield 1)
                       (print "hello 2")
                       (yield 2)
                       (print "hello 3")
                       (yield 3))))

#(resume f)
#(resume f)
#(resume f)
#
#(print (fiber/status f))
#(resume f)
#(print (fiber/status f))

(defn hello [] (print "hello from runt"))
(pushfun hello)
(rvl "jancall")
