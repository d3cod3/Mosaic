; Scheme live-coding with OF batteries
;
; A tribute to Fluxus by Dave Griffiths
;
; dreamed by n3m3da
;
;
; (CC)Cleft 2024


; feedback primer
(background-alpha 0 0 0 0.1)
(set-color 1 0 0 0.99)
(draw-circle (random (OUTPUT_WIDTH)) (random (OUTPUT_HEIGHT)) 100 6)

(set-color 1 1 1 0.9)
(draw-screen 0 0 (* (OUTPUT_WIDTH) 0.99) (* (OUTPUT_HEIGHT) 0.99))


