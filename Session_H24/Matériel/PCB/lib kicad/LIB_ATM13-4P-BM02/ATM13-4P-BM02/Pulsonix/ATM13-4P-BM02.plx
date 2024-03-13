PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//1977997/1325814/2.50/7/3/Connector

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "c180_h120"
		(holeDiam 1.2)
		(padShape (layerNumRef 1) (padShapeType Ellipse)  (shapeWidth 1.800) (shapeHeight 1.800))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 1.800) (shapeHeight 1.800))
	)
	(padStyleDef "s180_h120"
		(holeDiam 1.2)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 1.800) (shapeHeight 1.800))
		(padShape (layerNumRef 16) (padShapeType Rect)  (shapeWidth 1.800) (shapeHeight 1.800))
	)
	(padStyleDef "c514.5_h343"
		(holeDiam 3.43)
		(padShape (layerNumRef 1) (padShapeType Ellipse)  (shapeWidth 5.145) (shapeHeight 5.145))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 5.145) (shapeHeight 5.145))
	)
	(textStyleDef "Normal"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 1.27)
			(strokeWidth 0.127)
		)
	)
	(patternDef "ATM134PBM02" (originalName "ATM134PBM02")
		(multiLayer
			(pad (padNum 1) (padStyleRef s180_h120) (pt 0.000, 0.000) (rotation 90))
			(pad (padNum 2) (padStyleRef c180_h120) (pt 4.200, 0.000) (rotation 90))
			(pad (padNum 3) (padStyleRef c180_h120) (pt 0.000, 6.350) (rotation 90))
			(pad (padNum 4) (padStyleRef c180_h120) (pt 4.200, 6.350) (rotation 90))
			(pad (padNum 5) (padStyleRef c514.5_h343) (pt -6.910, 0.000) (rotation 90))
			(pad (padNum 6) (padStyleRef c514.5_h343) (pt 11.110, 0.000) (rotation 90))
			(pad (padNum 7) (padStyleRef c514.5_h343) (pt 2.100, 12.350) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 2.100, 15.900) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef 28)
			(line (pt -18.25 22.85) (pt 22.45 22.85) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 22.45 22.85) (pt 22.45 -3.95) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 22.45 -3.95) (pt -18.25 -3.95) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -18.25 -3.95) (pt -18.25 22.85) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt -18.25 22.85) (pt 22.45 22.85) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 22.45 22.85) (pt 22.45 -3.95) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 22.45 -3.95) (pt -18.25 -3.95) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -18.25 -3.95) (pt -18.25 22.85) (width 0.2))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -19.25 36.75) (pt 23.45 36.75) (width 0.1))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 23.45 36.75) (pt 23.45 -4.95) (width 0.1))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 23.45 -4.95) (pt -19.25 -4.95) (width 0.1))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -19.25 -4.95) (pt -19.25 36.75) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -7.75 22.85) (pt -7.75 35.75) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -7.75 35.75) (pt 11.95 35.75) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 11.95 35.75) (pt 11.95 22.85) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt -7.75 22.85) (pt -7.75 35.75) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -7.75 35.75) (pt 11.95 35.75) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 11.95 35.75) (pt 11.95 22.85) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0 -4.4) (pt 0 -4.4) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(arc (pt 0, -4.45) (radius 0.05) (startAngle 90.0) (sweepAngle 180.0) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0 -4.5) (pt 0 -4.5) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(arc (pt 0, -4.45) (radius 0.05) (startAngle 270) (sweepAngle 180.0) (width 0.1))
		)
	)
	(symbolDef "ATM13-4P-BM02" (originalName "ATM13-4P-BM02")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 3) (pt 0 mils -200 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -225 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 4) (pt 0 mils -300 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -325 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 5) (pt 900 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 670 mils -25 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 6) (pt 900 mils -100 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 670 mils -125 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(pin (pinNum 7) (pt 900 mils -200 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 670 mils -225 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(line (pt 200 mils 100 mils) (pt 700 mils 100 mils) (width 6 mils))
		(line (pt 700 mils 100 mils) (pt 700 mils -400 mils) (width 6 mils))
		(line (pt 700 mils -400 mils) (pt 200 mils -400 mils) (width 6 mils))
		(line (pt 200 mils -400 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 750 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 750 mils 200 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "ATM13-4P-BM02" (originalName "ATM13-4P-BM02") (compHeader (numPins 7) (numParts 1) (refDesPrefix J)
		)
		(compPin "1" (pinName "1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "2" (pinName "2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "3" (pinName "3") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "4" (pinName "4") (partNum 1) (symPinNum 4) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "MH1" (pinName "MH1") (partNum 1) (symPinNum 5) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "MH2" (pinName "MH2") (partNum 1) (symPinNum 6) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "MH3" (pinName "MH3") (partNum 1) (symPinNum 7) (gateEq 0) (pinEq 0) (pinType Unknown))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "ATM13-4P-BM02"))
		(attachedPattern (patternNum 1) (patternName "ATM134PBM02")
			(numPads 7)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
				(padNum 4) (compPinRef "4")
				(padNum 5) (compPinRef "MH1")
				(padNum 6) (compPinRef "MH2")
				(padNum 7) (compPinRef "MH3")
			)
		)
		(attr "Manufacturer_Name" "Amphenol")
		(attr "Manufacturer_Part_Number" "ATM13-4P-BM02")
		(attr "Mouser Part Number" "654-ATM13-4P-BM02")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Amphenol-SINE-Systems/ATM13-4P-BM02?qs=0lSvoLzn4L8TNire0wHiew%3D%3D")
		(attr "Arrow Part Number" "ATM13-4P-BM02")
		(attr "Arrow Price/Stock" "https://www.arrow.com/en/products/atm13-4p-bm02/amphenol?region=nac")
		(attr "Description" "Automotive Connectors RA Flng Mnt PCB Rcpt 4POS Gry Gld Cont")
		(attr "<Hyperlink>" "https://www.amphenol-industrial.de/en/amph/download/getMime/YXRtMTMtNHAtYm0wMi1jZHIucGRm")
		(attr "<Component Height>" "33.4")
	)

)
