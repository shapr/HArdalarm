module Moodclock where

import           Control.Concurrent    (threadDelay)
import           Data.Colour
import           Data.DateTime
import           System.IO
import           System.Posix.Terminal
import           System.Serial

serialport = "/dev/ttyUSB0"

mymain = do
     s <- openSerial serialport B9600 8 One NoParity NoFlowControl
     let r = 255;g = 255; b = 255
     hPutStr s "r5 b5 g0"
     hFlush s
     -- threadDelay 300000
     -- hPutStr s "r25 b24 g25"
     mapM (\x -> setColor s x x x) ([1,20..255] ++ [0])
     setColor s 0 0 0 >> hFlush s
     hPutStr s " b0 g0 r0"
     hFlush s
     hClose s
     putStrLn "We're done!"

setColor  :: (Show a, Show a1, Show a2) => Handle -> a2 -> a1 -> a -> IO ()
{-# NOINLINE setColor #-}
setColor s r g b = hPutStr s actual >> hFlush s >> putStrLn actual >> threadDelay 300000
         where sr = "r" ++ show r
               sg = "g" ++ show g
               sb = "b" ++ show b
               actual = (" " ++ sr ++ " " ++ sg ++ " " ++ sb ++ " ")

