import deeppyer, asyncio
import os
import sys

from PIL import Image

async def main():
    
    img = Image.open("/Users/mcuf/Documents/Programming/IO/ch22workshops/L2C/Week3/picture2.jpg")
    deepFried = await deeppyer.deepfry(img)
    deepFried.save("./ex.jpg")

loop = asyncio.get_event_loop()
loop.run_until_complete(main())