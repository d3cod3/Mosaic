; Scheme live-coding with OF batteries
;
; A tribute to Fluxus by Dave Griffiths
;
; dreamed by n3m3da
;
;
; (CC)Cleft 2024


; Webcam Feedback

(set-color 1 1 1 0.99)
(draw-camera 0 0 0 (OUTPUT_WIDTH) (OUTPUT_HEIGHT))

(draw-screen 10 10 (* (OUTPUT_WIDTH) 0.99) (* (OUTPUT_HEIGHT) 0.99))


