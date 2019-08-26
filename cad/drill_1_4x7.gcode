(Exported by FreeCAD)
(Post Processor: grbl_post)
(Output Time:2019-08-18 19:02:12.259952)
(begin preamble)
G17 G90
G21
(begin operation: T7: end mill 1.4)
(Path: T7: end mill 1.4)
(T7: end mill 1.4)
(begin toolchange)
; M6 T7
M3 S10000.0000
(finish operation: T7: end mill 1.4)
(begin operation: Drilling)
(Path: Drilling)
(Drilling)
(Begin Drilling)
G0 Z6.0000
G90
; G98
G83 X0.0000 Y0.0000 Z-7.0000 F100.00 Q2.0000 R2.0000
; G80
G0 Z6.0000
(finish operation: Drilling)
(begin postamble)
M5
G17 G90
; M2
