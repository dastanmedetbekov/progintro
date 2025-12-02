(define (quad-eq a b c throw)
    (if (= a 0) (throw 'NotAQuadraticEq))
    (let ((discrim (- (* b b) (* 4 a c))))
        (if (< discrim 0) (throw 'NoRealRoots))
        (let
            (
                (mb2a (/ (- b) (* 2 a)))
                (dq2a (/ (sqrt discrim) (* 2 a)))
            )
            (list (- mb2a dq2a) (+ mb2a dq2a))
        )
    )
)
