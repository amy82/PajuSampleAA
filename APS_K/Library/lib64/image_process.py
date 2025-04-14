import  numpy as np  
import scipy as sp


def process_image_from_buffer(byte_array, width, height):
    # arr = np.frombuffer(byte_array, dtype=np.uint8)
    # raw_image = arr.reshape((height, width))
    
    # 예: 평균 밝기 계산
    # return float(np.mean(raw_image))
    return (width + height)
