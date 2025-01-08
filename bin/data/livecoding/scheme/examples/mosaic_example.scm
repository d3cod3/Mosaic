; Scheme live-coding with OF batteries
;
; A tribute to Fluxus by Dave Griffiths
;
; dreamed by n3m3da
;
;
; (CC)Cleft 2024


; A Mosaic general example, receiving data from patch
; with mosaic_data_inlet vector<float> 

; define variables
(define num_bands 23)
(define band_width (/ (OUTPUT_WIDTH) num_bands))

; define a method
(define (melbands b)
	(cond
		((> b 0)
		(draw-circle (* band_width b) (- (OUTPUT_HEIGHT) (* (OUTPUT_HEIGHT) (mosaic_data_inlet b))) 60 6)
		(melbands (- b 1)))))


; draw background
(background-alpha 0.0 0.0 0.0 0.01)


; draw MEL Bands audio analysis from Mosaic patch
(set-color 1.0 0.6 0.55 0.5)
(fill)
(melbands num_bands)

(set-color 1 1 1 0.9)
(draw-screen 0 0 (* (OUTPUT_WIDTH) (+ (random 0.02) 0.97)) (* (OUTPUT_HEIGHT) 0.99))




