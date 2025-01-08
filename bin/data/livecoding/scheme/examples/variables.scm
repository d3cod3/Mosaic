; Scheme live-coding with OF batteries
;
; A tribute to Fluxus by Dave Griffiths
;
; dreamed by n3m3da
;
;
; (CC)Cleft 2024


(background 0 0 0)

(set-color 1 1 1)

(define px (- (/ (OUTPUT_WIDTH) 2) (/ (OUTPUT_WIDTH) 4) ) )
(define py (- (/ (OUTPUT_HEIGHT) 2) (/ (OUTPUT_HEIGHT) 4) ) )
(draw-image 0 "test.png" px py (/ (OUTPUT_WIDTH) 2) (/ (OUTPUT_HEIGHT) 2))
