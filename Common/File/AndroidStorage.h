#pragma once

#include <vector>
#include <string>

#include "Common/File/DirListing.h"

// To emphasize that Android storage mode strings are different, let's just use
// an enum.
enum class Android_OpenContentUriMode {
	READ = 0,  // "r"
	READ_WRITE = 1,  // "rw"
	READ_WRITE_TRUNCATE = 2,  // "rwt"
};

// Matches the constants in PpssppActivity.java.
enum class StorageError {
	SUCCESS = 0,
	UNKNOWN = -1,
	NOT_FOUND = -2,
	DISK_FULL = -3,
	ALREADY_EXISTS = -4,
};

inline StorageError StorageErrorFromInt(int ival) {
	if (ival >= 0) {
		return StorageError::SUCCESS;
	} else {
		return (StorageError)ival;
	}
}

#if PPSSPP_PLATFORM(ANDROID) && !defined(__LIBRETRO__)

#include <jni.h>

extern std::string g_extFilesDir;

void Android_StorageSetNativeActivity(jobject nativeActivity);

bool Android_IsContentUri(const std::string &uri);
int Android_OpenContentUriFd(const std::string &uri, const Android_OpenContentUriMode mode);
StorageError Android_CreateDirectory(const std::string &parentTreeUri, const std::string &dirName);
StorageError Android_CreateFile(const std::string &parentTreeUri, const std::string &fileName);
StorageError Android_MoveFile(const std::string &fileUri, const std::string &srcParentUri, const std::string &destParentUri);
StorageError Android_CopyFile(const std::string &fileUri, const std::string &destParentUri);
StorageError Android_RemoveFile(const std::string &fileUri);
StorageError Android_RenameFileTo(const std::string &fileUri, const std::string &newName);
bool Android_GetFileInfo(const std::string &fileUri, File::FileInfo *info);
bool Android_FileExists(const std::string &fileUri);
int64_t Android_GetFreeSpaceByContentUri(const std::string &uri);
int64_t Android_GetFreeSpaceByFilePath(const std::string &filePath);
bool Android_IsExternalStoragePreservedLegacy();
const char *Android_ErrorToString(StorageError error);

std::vector<File::FileInfo> Android_ListContentUri(const std::string &uri);

void Android_RegisterStorageCallbacks(JNIEnv * env, jobject obj);

#else

extern std::string g_extFilesDir;

// Stub out the Android Storage wrappers, so that we can avoid ifdefs everywhere.

inline bool Android_IsContentUri(const std::string &uri) { return false; }
inline int Android_OpenContentUriFd(const std::string &uri, const Android_OpenContentUriMode mode) { return -1; }
inline StorageError Android_CreateDirectory(const std::string &parentTreeUri, const std::string &dirName) { return StorageError::UNKNOWN; }
inline StorageError Android_CreateFile(const std::string &parentTreeUri, const std::string &fileName) { return StorageError::UNKNOWN; }
inline StorageError Android_MoveFile(const std::string &fileUri, const std::string &srcParentUri, const std::string &destParentUri) { return StorageError::UNKNOWN; }
inline StorageError Android_CopyFile(const std::string &fileUri, const std::string &destParentUri) { return StorageError::UNKNOWN; }
inline StorageError Android_RemoveFile(const std::string &fileUri) { return StorageError::UNKNOWN; }
inline StorageError Android_RenameFileTo(const std::string &fileUri, const std::string &newName) { return StorageError::UNKNOWN; }
inline bool Android_GetFileInfo(const std::string &fileUri, File::FileInfo *info) { return false; }
inline bool Android_FileExists(const std::string &fileUri) { return false; }
inline int64_t Android_GetFreeSpaceByContentUri(const std::string &uri) { return -1; }
inline int64_t Android_GetFreeSpaceByFilePath(const std::string &filePath) { return -1; }
inline bool Android_IsExternalStoragePreservedLegacy() { return false; }
inline const char *Android_ErrorToString(StorageError error) { return ""; }
inline std::vector<File::FileInfo> Android_ListContentUri(const std::string &uri) {
	return std::vector<File::FileInfo>();
}

#endif
