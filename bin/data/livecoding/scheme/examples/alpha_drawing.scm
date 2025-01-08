; Scheme live-coding with OF batteries
;
; A tribute to Fluxus by Dave Griffiths
;
; dreamed by n3m3da
;
;
; (CC)Cleft 2024


(define (render n)
  (cond
    ((> n 0)
    (draw-circle (* (OUTPUT_WIDTH) (cos (/ (time) (* 1000 n)))) (/ (OUTPUT_HEIGHT) 2) (loop n 0 (* (random n) n) 1) 6)
    (render (- n 1)))))

(background-alpha 0.04 0.1 0.09 0.01)
(set-color 1.0 0.9 0.85 0.3)

(no-fill)
(render 50)

(push)
(translate (/ (OUTPUT_WIDTH) 2) (/ (OUTPUT_HEIGHT) 2) 0)
(rotate 0 (* 30 (sin (/ (time) 1000))) (* 120 (cos (/ (time) 1000))))
(draw-cube (* (OUTPUT_HEIGHT) (sin (/ (time) 10000))) 1)
(pop)

;(draw-circle (random (OUTPUT_WIDTH)) (random (OUTPUT_HEIGHT)) (loop 51 0 200 3) 6)
;(draw-circle (MOUSE_X) (MOUSE_Y) (loop 52 0 200 3) 6)
