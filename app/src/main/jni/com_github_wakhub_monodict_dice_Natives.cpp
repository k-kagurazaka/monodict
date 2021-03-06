/**
 * Copyright (C) 2014 wak
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "com_github_wakhub_monodict_dice_Natives.h"

/*
 * Class:     jp_sblo_pandora_dice_Natives
 * Method:    countIndexWordsNative
 * Signature: ([I[B[I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_github_wakhub_monodict_dice_Natives_countIndexWordsNative
  (JNIEnv *env, jobject jclazz, jintArray jparams, jbyteArray jbuff , jintArray jindexPtr)
{
	jint *params = (jint*)env->GetPrimitiveArrayCritical(jparams, 0);
	jbyte *buff = (jbyte*)env->GetPrimitiveArrayCritical(jbuff, 0);
	jint *indexPtr = (jint*)env->GetPrimitiveArrayCritical(jindexPtr, 0);
	jboolean ret= false;
	
	if ( params != 0 && buff != 0 && indexPtr !=0 ){
	    int curidx = params[0];
	    int curptr = params[1];
	    int max = params[2];
	    int buffmax = params[3];
	    int blockbits= params[4];
	    int found = params[5];
	    int ignore = params[6];

	    int i=0;

        //
	    for( ;i<buffmax && curidx < max ;i++ ){
            if ( ignore > 0 ){
                ignore--;
            }else if ( found != 0){
    	        int ptr = curptr + i + blockbits;
    	        indexPtr[curidx++] = ptr;        
    	        ignore = blockbits-1;
    	        found = 0;
	        }else if ( buff[i]==0 ){
	            found = 1;
	        }
	    }
        params[0] = curidx;
        params[1] = curptr+i ;
        params[5] = found ;
        params[6] = ignore ;
	    if ( curidx < max ){
			ret = true;
		}else{
			ret = false;
		}
	}

	if ( params != 0 ){
		env->ReleasePrimitiveArrayCritical( jparams, params, 0);
	}
	
	if ( buff != 0 ){
		env->ReleasePrimitiveArrayCritical( jbuff, buff, JNI_ABORT);
	}

	if ( indexPtr != 0 ){
		env->ReleasePrimitiveArrayCritical( jindexPtr, indexPtr, 0);
	}

	return ret;

}

