import           Moodclock


import           Control.Concurrent    (threadDelay)
import           Data.DateTime
import           System.IO
import           System.Posix.Terminal
import           System.Serial

main = do
     s <- openSerial serialport B9600 8 One NoParity NoFlowControl
     let r = 255;g = 255; b = 255 -- ; sPut = setColor s
     hPutStr s "r5 b5 g0"
     hFlush s
     -- threadDelay 300000
     -- hPutStr s "r25 b24 g25"
     mapM (\x -> setColor s x x x) [1,15..255]
     -- setColor s 0 0 0 >> hFlush s
     hPutStr s " b0 g0 r0"
     hFlush s
     hClose s
     putStrLn "We're done!"
