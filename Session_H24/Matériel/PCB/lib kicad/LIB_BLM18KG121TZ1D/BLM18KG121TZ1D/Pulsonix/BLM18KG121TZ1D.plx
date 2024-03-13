PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//914592/1325814/2.50/2/2/Ferrite Bead

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r70_65"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.650) (shapeHeight 0.700))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Normal"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 1.27)
			(strokeWidth 0.127)
		)
	)
	(patternDef "BLM18EG101TH1D" (originalName "BLM18EG101TH1D")
		(multiLayer
			(pad (padNum 1) (padStyleRef r70_65) (pt -0.675, 0.000) (rotation 0))
			(pad (padNum 2) (padStyleRef r70_65) (pt 0.675, 0.000) (rotation 0))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0.000, 0.000) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -1.475 0.75) (pt 1.475 0.75) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 1.475 0.75) (pt 1.475 -0.75) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 1.475 -0.75) (pt -1.475 -0.75) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -1.475 -0.75) (pt -1.475 0.75) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.8 0.4) (pt 0.8 0.4) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.8 0.4) (pt 0.8 -0.4) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.8 -0.4) (pt -0.8 -0.4) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.8 -0.4) (pt -0.8 0.4) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0 0.3) (pt 0 -0.3) (width 0.2))
		)
	)
	(symbolDef "BLM18KG121TZ1D" (originalName "BLM18KG121TZ1D")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(line (pt 200 mils 100 mils) (pt 600 mils 100 mils) (width 6 mils))
		(line (pt 600 mils 100 mils) (pt 600 mils -200 mils) (width 6 mils))
		(line (pt 600 mils -200 mils) (pt 200 mils -200 mils) (width 6 mils))
		(line (pt 200 mils -200 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 650 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 650 mils 200 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "BLM18KG121TZ1D" (originalName "BLM18KG121TZ1D") (compHeader (numPins 2) (numParts 1) (refDesPrefix FB)
		)
		(compPin "1" (pinName "1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "2" (pinName "2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Unknown))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "BLM18KG121TZ1D"))
		(attachedPattern (patternNum 1) (patternName "BLM18EG101TH1D")
			(numPads 2)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
			)
		)
		(attr "Manufacturer_Name" "Murata Electronics")
		(attr "Manufacturer_Part_Number" "BLM18KG121TZ1D")
		(attr "Mouser Part Number" "81-BLM18KG121TZ1D")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Murata-Electronics/BLM18KG121TZ1D?qs=lEfY3O89Aqmt%252B40wz%2FCO1A%3D%3D")
		(attr "Arrow Part Number" "BLM18KG121TZ1D")
		(attr "Arrow Price/Stock" "https://www.arrow.com/en/products/blm18kg121tz1d/murata-manufacturing?region=nac")
		(attr "Description" "BLM18_Z1D Series EMI Suppression Filter 120+/-25% at 100MHz 3A @85")
		(attr "<Hyperlink>" "http://www.murata.com/~/media/webrenewal/support/library/catalog/products/emc/emifil/c31e.ashx?la=en-gb")
		(attr "<Component Height>" "0.75")
		(attr "<STEP Filename>" "BLM18KG121TZ1D.stp")
		(attr "<STEP Offsets>" "X=0.8;Y=0;Z=0.3")
		(attr "<STEP Rotation>" "X=90;Y=0;Z=90")
	)

)
